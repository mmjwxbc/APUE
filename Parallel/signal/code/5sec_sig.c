#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
int64_t cnt = 0;
static volatile int loop = 1;
static void alarm_handler(int s)
{
    loop = 0;
}

int main()
{
    signal(SIGALRM, alarm_handler);
    alarm(5);
    while(loop)
    {
        cnt ++;
    }
    printf("%ld\n", cnt);
    exit(0);
}