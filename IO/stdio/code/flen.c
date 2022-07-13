#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *fp;
    int count = 0;
    if(argc < 2)
    {
        fprintf(stderr, "Usage...\n");
        exit(1);
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL)
    {
        perror("fopen()");
        exit(1);
    }
    long len = 0;
    fseek(fp, 0, SEEK_END);
    len = ftell(fp);
    printf("File Size = %ld\n", len);
    fclose(fp);
    exit(0);
}