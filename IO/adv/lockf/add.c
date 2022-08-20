#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#define PROCNUM 20
#define FNAME "/tmp/out"
#define LINESIZE 1024


static void func_add()
{   
    FILE *fp = fopen(FNAME, "r+");
    char linebuf[LINESIZE];
    if(fp == NULL)
    {
        perror("fopen()");
        exit(1);
    }
    int fd = fileno(fp);
    lockf(fd, F_LOCK, 0);
    fgets(linebuf, LINESIZE, fp);
    fseek(fp, 0, SEEK_SET);
    fprintf(fp, "%d\n", atoi(linebuf) + 1);
    lockf(fd, F_ULOCK, 0);
    fflush(NULL);
    fclose(fp);
    return;
}
int main()
{
    int pid;
    for(int i = 0; i < PROCNUM; i++)
    {
        pid = fork();
        if(pid < 0)
        {
            perror("fork()");
            exit(1);
        }
        if(pid == 0)
        {
            func_add();
            exit(0);
        }
    }

    for(int i = 0; i < PROCNUM; i++)
        wait(NULL);

    exit(0);
}