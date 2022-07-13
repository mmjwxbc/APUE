#include <stdio.h>
#include <stdlib.h>
ssize_t mygetline(char **lineptr, size_t *n, FILE *stream)
{
    if(lineptr == NULL || *n == 0)
    {
        *lineptr = (char *)malloc(10);
        *n = 10;
    }
    ssize_t write_cnt = 0;
    char ch;
    while((ch = fgetc(stream)) != '\n')
    {
        if(ch == EOF)
            return -1;
        if(write_cnt < *n - 2)
        {
            (*lineptr)[write_cnt ++] = ch;
        }
        else
        {
            *n += 10;
            *lineptr = (char*)realloc(*lineptr, *n);
            (*lineptr)[write_cnt ++] = ch;
        }
    }
    (*lineptr)[write_cnt ++] = '\n';
    (*lineptr)[write_cnt ++] = '\0';
    return write_cnt;
}