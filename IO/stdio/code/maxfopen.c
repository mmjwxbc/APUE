#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
// ubuntu open files 1048576
int main()
{
    FILE *fp;
    int cnt = 0;
    while(1)
    {
        fp = fopen("tmp","w");
        if(fp == NULL)
        {
            perror("fopen()");
            break;
        }
        cnt ++;
    }
    printf("max = %d\n", cnt);
    fclose(fp);
    exit(0);
}