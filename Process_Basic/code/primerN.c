#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define LEFT    30000000
#define RIGHT   30000200
#define N       3
int main()
{
    int mark, n;
    pid_t pid;

    for(n = 0; n < N; n ++)
    {
        pid = fork();
        if(pid < 0)
        {
            perror("fork()");
            exit(1);
        }
        if(pid == 0)
        {
            for(int i = LEFT + n; i <= RIGHT; i += N)
            {
                if(pid < 0)
                {
                    perror("fork()");
                    exit(1);
                }

                for(int j = 2; j < i / 2; j ++)
                {
                    mark = 1;
                    if(i % j == 0)
                    {
                        mark = 0;
                        break;
                    }
                }
                if(mark)
                    printf("[%d]%d is a primer\n", n, i);
            }
            exit(0);
        }
    }
    int st;
    for(int i = 0; i < N; i ++)
    {
        wait(&st);
    }
    exit(0);
}