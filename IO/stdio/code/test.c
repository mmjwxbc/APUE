#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUFSIZE 5
char buf[BUFSIZE];
int main()
{
    FILE *fp;
    fp = fopen("tmp.txt","r");
    int cnt = 0;
    while(fgets(buf, BUFSIZE, fp) != NULL)
    {
        // puts(buf);
        printf("%d\n", buf[0]); // 'a' 第二次输出换行键
        cnt ++;
    }
    printf("cnt  = %d\n", cnt);
    exit(0);
}