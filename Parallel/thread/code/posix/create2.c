#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
static void *func(void *p)
{
    
}
int main()
{
    int i, err;
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, 1024);
    for(i = 0; ; i++)
    {
        err = pthread_create(&tid, &attr, func, NULL);
        if(err)
        {
            fprintf(stderr, "%s", strerror(err));
            break;
        }
    }
    printf("%d\n", i);
    pthread_attr_destroy(&attr);
    exit(0);
}