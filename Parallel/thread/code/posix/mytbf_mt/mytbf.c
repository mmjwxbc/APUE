#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include "mytbf.h"
#include <pthread.h>
#include <string.h>

// typedef void (*sighandler_t)(int);
static pthread_mutex_t mut_job = PTHREAD_MUTEX_INITIALIZER;
static struct mytbf_st *job[MYTBF_MAX];
static int inited = 0;
static pthread_t tid_alarm;
static pthread_once_t once_init = PTHREAD_ONCE_INIT;
// static sighandler_t alrm_handler_save;
struct mytbf_st
{
    int cps;
    int burst;
    int token;
    int pos;
    pthread_mutex_t mut;
    pthread_cond_t cond;
};

static void* thr_alrm(void *p)
{
    while(1)
    {
        int i;
        pthread_mutex_lock(&mut_job);
        for(i = 0; i < MYTBF_MAX; i ++)
        {
            if(job[i] != NULL)
            {
                pthread_mutex_lock(&job[i]->mut);
                job[i]->token += job[i]->cps;
                if(job[i]->token > job[i]->burst)
                    job[i]->token = job[i]->burst;
                pthread_mutex_unlock(&job[i]->mut);
            }
        }
        pthread_cond_broadcast(&job[i]->cond);
        pthread_mutex_unlock(&mut_job);
        sleep(1);
    }

}

static void module_unload()
{
    // signal(SIGALRM, alrm_handler_save);
    // alarm(0);

    pthread_cancel(tid_alarm);
    pthread_join(tid_alarm, NULL);
    for(int i = 0; i < MYTBF_MAX; i ++)
    {
        if(job[i] != NULL)
        {
            mytbf_destory(job[i]);
        }
    }
    pthread_mutex_destroy(&mut_job);
}

static void module_load()
{
    // alrm_handler_save = signal(SIGALRM, alrm_handler);
    // alarm(1);
    int err;
    err = pthread_create(&tid_alarm, NULL, thr_alrm, NULL);
    if(err)
    {
        fprintf(stderr, "pthread_create():%s\n", strerror(err));
        exit(1);
    }
    atexit(module_unload);
}

int get_free_pos_unlocked()
{
    for(int i = 0; i < MYTBF_MAX; i ++)
        if(job[i] == NULL)
            return i;
    return -1;
}
mytbf_t* mytbf_init(int cps, int burst)
{
    struct mytbf_st *me;
    // if(!inited)
    // {
    //     module_load();
    //     inited = 1;
    // }
    pthread_once(&once_init, module_load);

    me = malloc(sizeof(*me));
    if(me == NULL)
        return NULL;
    me->token = 0;
    me->cps = cps;
    me->burst = burst;
    pthread_mutex_init(&me->mut, NULL);
    pthread_cond_init(&me->cond, NULL);

    pthread_mutex_lock(&mut_job);
    int pos = get_free_pos_unlocked();
    if(pos < 0)
    {
        pthread_mutex_unlock(&mut_job);
        free(me);
        return NULL;
    }
    me->pos = pos;
    job[pos] = me;
    pthread_mutex_unlock(&mut_job);
    return me;
}
int min(int a, int b)
{
    if(a > b)
        return b;
    return a;
}

int mytbf_fetchtoken(mytbf_t *ptr, int size)
{
    struct mytbf_st *me = ptr;
    if(size <= 0)
        return -EINVAL;
    pthread_mutex_lock(&me->mut);
    while(me->token <= 0)
    {
        pthread_cond_wait(&me->cond, &me->mut);
        // pthread_mutex_unlock(&me->mut);
        // sched_yield();
        // pthread_mutex_lock(&me->mut);
    }
    int n = min(me->token, size);
    me->token -= n;
    pthread_mutex_unlock(&me->mut);
    return n;
}

int mytbf_returntoken(mytbf_t *ptr, int size)
{
    struct mytbf_st *me = ptr;
    if(size <= 0)
        return -EINVAL;
    pthread_mutex_lock(&me->mut);
    me->token += size;
    if(me->token > me->burst)
        me->token = me->burst;
    pthread_cond_broadcast(&me->cond);
    pthread_mutex_unlock(&me->mut);    
    return size;
}

int mytbf_destory(mytbf_t *ptr)
{
    struct mytbf_st *me = ptr;

    pthread_mutex_lock(&mut_job);
    job[me->pos] = NULL;
    pthread_mutex_unlock(&mut_job);
    pthread_mutex_destroy(&me->mut);
    pthread_cond_destroy(&me->cond);
    free(ptr);
    return 0;
}