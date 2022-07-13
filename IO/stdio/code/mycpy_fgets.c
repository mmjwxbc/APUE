#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BUFSIZE 1024
char buf[BUFSIZE];
int main(int argc, char **argv)
{
    if(argc != 3)
    {
        fprintf(stderr, "Usage: ./mycpy <src_file> <dst_file>\n");
        exit(1);
    }
    FILE *fdr = fopen(argv[1], "r");
    if(fdr == NULL)
    {
        perror("fopen()");
        exit(1);
    }
    FILE *fdw = fopen(argv[2], "w");
    if(fdw == NULL)
    {
        fclose(fdr);
        perror("fopen()");
        exit(1);
    }
    int ch;
    while(fgets(buf, BUFSIZE, fdr) != NULL)
    {
        if(fputs(buf, fdw) == EOF)
        {
            perror("fputc()");
            break;
        }
    }
    fclose(fdr);
    fclose(fdw);
    exit(0);
}