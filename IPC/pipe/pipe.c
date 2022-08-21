#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#define BUFSIZE 1024
int main()
{
    int pipefd[2];
    int pid;
    char buf[BUFSIZE];
    if(pipe(pipefd) < 0) {
        perror("pipe()");
        exit(1);
    }
    pid = fork();
    if(pid == 0) {
        close(pipefd[1]);
        int len = read(pipefd[0], buf, BUFSIZE);
        write(1, buf, len);
        close(pipefd[0]);
        exit(0);
    } else {
        close(pipefd[0]);
        write(pipefd[1], "Hello!\n", 7);
        close(pipefd[1]);
        wait(NULL);
    }
    exit(0);
}