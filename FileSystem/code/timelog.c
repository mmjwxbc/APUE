#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define FNAME "/tmp/out"
#define BUFSIZE 1024
int main()
{
    FILE *fp = fopen(FNAME, "a+");
    char buf[BUFSIZE];
    int cnt = 0;
    time_t stamp;
    struct tm *tm;
    if(fp == NULL)
    {
        perror("fopen()");
        exit(0);
    }
    while(fgets(buf, BUFSIZE, fp) != NULL)
        cnt ++;
    while(1)
    {
        time(&stamp);
        tm = localtime(&stamp);
        fprintf(fp, "%4d %d-%d-%d %d:%d:%d\n", ++cnt, tm -> tm_year + 1900, tm -> tm_mon + 1, tm->tm_mday, tm->tm_hour, tm -> tm_min, tm -> tm_sec);
        fflush(fp);
        sleep(1);
        printf("%d", cnt);
    }
    fclose(fp);
    exit(0);
}