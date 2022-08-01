#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include "mytbf.h"
#include <string.h>
#define CPS 10
#define BUFSIZE CPS
#define BURST 100

int main(int argc, char **argv)
{
    char buf[BUFSIZE];
    mytbf_t *tbf;
    if(argc < 2)
    {
        fprintf(stderr, "Usage...\n");
        exit(1);
    }

    tbf = mytbf_init(CPS, BURST);


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
    int size;
    while(1)
    {
        size = mytbf_fetchtoken(tbf, BUFSIZE);
        if(size < 0)
        {
            fprintf(stderr, "mytbf_fetchtoken():%s\n", strerror(-size));
            exit(1);
        }
        int len;
        while((len = read(fdr, buf, size)) < 0)
        {
            if(errno == EINTR)
                continue;
            perror("read()");
            break;
        }
        if(size - len > 0)
            mytbf_returntoken(tbf, size - len);
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
    mytbf_destory(tbf);
    close(fdr);
    close(fdw);
    exit(0);
}