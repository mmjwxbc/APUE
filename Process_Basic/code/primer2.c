#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define LEFT    30000000
#define RIGHT   30000200

int main()
{
    int mark;
    pid_t pid;
    for(int i = LEFT; i <= RIGHT; i ++)
    {
        pid = fork();
        if(pid < 0)
        {
            perror("fork()");
            exit(1);
        }

        if(pid == 0)
        {
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
                printf("%d is a primer\n", i);
            exit(0);
        }
    }
    int st;
    for(int i = LEFT; i <= RIGHT; i ++)
    {
        wait(&st);
    }
    exit(0);
}