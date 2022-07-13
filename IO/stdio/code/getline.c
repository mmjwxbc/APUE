#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mygetline.h"

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        fprintf(stderr, "Usage...\n");
        exit(1);
    }

    FILE *fp = fopen(argv[1], "r");
    char *linebuf = NULL;
    size_t linesize = 0;
    if(fp == NULL)
    {
        perror("fopen()");
        exit(1);
    }
    while (1)
    {
        if(getline(&linebuf, &linesize, fp) < 0)
        {
            break;
        }
        printf("%ld\n", strlen(linebuf));
    }
    
    fclose(fp);
    exit(0);
}