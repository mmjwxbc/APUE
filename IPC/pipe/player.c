#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
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
        dup2(pipefd[0], 0); // 将exec的进程的输入端重定向
        close(pipefd[0]);
        int fd = open("/dev/null", O_RDWR);
        dup2(fd, 1);
        dup2(fd, 2);
        execl("/usr/bin/mpg123", "mpg123", "-", NULL);
        perror("execl()");
        exit(1);
    } else {
        close(pipefd[0]);
        write(pipefd[1], "Hello!\n", 7);
        close(pipefd[1]);
        wait(NULL);
    }
    exit(0);
}