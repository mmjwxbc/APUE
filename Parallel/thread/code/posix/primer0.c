#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define LEFT    30000000
#define RIGHT   30000200
#define THRNUM  (RIGHT - LEFT + 1)

static void *thr_prime(void *p)
{
    int i = (int)p;
    int mark;
    mark = 1;
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
    pthread_exit(NULL);
}
int main()
{
    int i;
    int err;
    pthread_t tid[THRNUM];
    for(i = LEFT; i <= RIGHT; i++)
    {
        err = pthread_create(tid + i - LEFT, NULL, thr_prime,(void *) i);
        if(err)
        {
            fprintf(stderr, "pthread_create():%s\n", strerror(err));
            exit(1);
        }
    }
    for(i = LEFT; i <= RIGHT; i++)
    {
        pthread_join(tid[i - LEFT], NULL);
    }
    exit(0);
}