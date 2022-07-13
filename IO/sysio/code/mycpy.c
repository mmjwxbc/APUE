#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUFSIZE 1048576

int main(int argc, char **argv)
{
    char buf[BUFSIZE];
    if(argc < 3)
    {
        fprintf(stderr, "Usage...\n");
        exit(1);
    }
    int fdr = open(argv[1], O_RDONLY);
    if(fdr < 0)
    {
        perror("open()");
        exit(1);
    }
    int fdw = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if(fdw < 0)
    {
        perror("open()");
        close(fdr);
        exit(1);
    }
    while(1)
    {
        int len = read(fdr, buf, BUFSIZE);
        if(len < 0)
        {
            perror("read()");
            break;
        }
        if(len == 0)
            break;
        int pos = 0;
        while(len > 0)
        {
            int ret = write(fdw, buf + pos, len);
            if(ret < 0)
            {
                perror("write()");
                exit(1);
            }
            pos += ret;
            len -= ret;  
        }      
    }
    close(fdr);
    close(fdw);
    exit(0);
}