#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define LEFT    30000000
#define RIGHT   31000000
#define THRNUM  4

static int num;
static pthread_mutex_t mut_num = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static void *thr_prime(void *p)
{
    while(1)
    {
        // int i = (int)p;
        int mark = 1;
        pthread_mutex_lock(&mut_num);
        while(num == 0)
        {
            pthread_cond_wait(&cond, &mut_num);
        }
        if(num == -1)
        {
            pthread_mutex_unlock(&mut_num);
            break;
        }
        int i = num;
        num = 0;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mut_num);
        for(int j = 2; j < i / 2; j ++)
        {
            if(i % j == 0)
            {
                mark = 0;
                break;
            }
        }
        if(mark)
        {
            printf("prime: %d\n", i);
        }
    }
    pthread_exit(NULL);
}
int main()
{
    int i;
    int err;
    pthread_t tid[THRNUM];
    for(i = 0; i <= THRNUM; i++)
    {
        err = pthread_create(tid + i, NULL, thr_prime,NULL);
        if(err)
        {
            fprintf(stderr, "pthread_create():%s\n", strerror(err));
            exit(1);
        }
    }

    for(int i = LEFT; i <= RIGHT; i++)
    {
        pthread_mutex_lock(&mut_num);
        while(num != 0)
        {
            pthread_cond_wait(&cond, &mut_num);
            // pthread_mutex_unlock(&mut_num);
            // sched_yield();
            // pthread_mutex_lock(&mut_num);
        }
        num = i;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mut_num);
    }

    pthread_mutex_lock(&mut_num);
    while(num != 0)
    {
        pthread_cond_wait(&cond, &mut_num);
        // pthread_mutex_unlock(&mut_num);
        // sched_yield();
        // pthread_mutex_lock(&mut_num);
    }
    num = -1;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mut_num);

    for(i = 0; i <= THRNUM; i++)
    {
        pthread_join(tid[i], NULL);
    }

    pthread_mutex_destroy(&mut_num);
    pthread_cond_destroy(&cond);
    exit(0);
}