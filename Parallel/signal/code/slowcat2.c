#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#define CPS 10
#define BUFSIZE CPS
#define BURST 100
static volatile int token = 0;

static void alrm_handler()
{
    alarm(1);
    token++;
    if(token > BURST)
        token = BURST;
}

int main(int argc, char **argv)
{
    char buf[BUFSIZE];
    if(argc < 2)
    {
        fprintf(stderr, "Usage...\n");
        exit(1);
    }

    signal(SIGALRM, alrm_handler);
    alarm(1);
    int fdr;
    do{
        fdr = open(argv[1], O_RDONLY);
        if(fdr < 0)
        {
            if(errno != EINTR)
            {
                perror("open()");
                exit(1);
            }
        }
    }while(fdr < 0);
    int fdw = 1;

    while(1)
    {
        while(token <= 0)
            pause();
        token--;
        int len;
        while((len = read(fdr, buf, BUFSIZE)) < 0)
        {
            if(errno == EINTR)
                continue;
            perror("read()");
            break;
        }
        int pos = 0;
        while(len > 0)
        {
            int ret = write(fdw, buf + pos, len);
            if(ret < 0)
            {
                if(errno == EINTR)
                    continue;
                perror("write()");
                exit(1);
            }
            pos += ret;
            len -= ret;  
        }      
        sleep(1);
    }
    close(fdr);
    close(fdw);
    exit(0);
}