#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

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
    while((ch = fgetc(fdr)) != EOF)
    {
        if(fputc(ch, fdw) == EOF)
        {
            perror("fputc()");
            break;
        }
    }
    fclose(fdr);
    fclose(fdw);
    exit(0);
}