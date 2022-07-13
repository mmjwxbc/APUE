#include <stdio.h>
#include <stdlib.h>
// #define BUFSIZE 1024
// ssize_t mygetline(char **lineptr, size_t *n, FILE *stream)
// {
//     size_t total = 0;
//     if(lineptr == NULL || *n == 0)
//     {
//         *lineptr = (char *)malloc(10);
//         *n = 10;
//     }
//     char *buf = *lineptr;
//     ssize_t write_cnt = 0;
//     char ch;
//     while((ch = fgetc(stream)) != '\n')
//     {
//         if(ch == EOF)
//             return -1;
//         if(write_cnt < *n - 2)
//         {
//             *(buf + write_cnt ++) = ch;
//         }
//         else
//         {
//             *n += 10;
//             buf = (char*)realloc(buf, *n);
//             *(buf + write_cnt ++) = ch;
//         }
//     }
//     *(buf + write_cnt ++) = '\n';
//     *(buf + write_cnt) = '\0';
//     return write_cnt;
// }

ssize_t mygetline(char** line,size_t *n,FILE *fp)
{
    char *buf = *line;
    ssize_t c,i=0;//i来记录字符串长度，c来存储字符
    if(buf==NULL||*n==0)
    {
        *line = (char *)malloc(10);
        buf = *line;
        *n = 10;
    }
    //buf为或n为0时动态为期分配空间
    while((c=fgetc(fp))!='\n')
    {
        if(c==EOF)
            return -1;
        if(i<*n-2)//留2个空间给\n和\0
        {
            *(buf+i++)=c;
        }
        else
        {
            *n = *n+10;
            buf = (char *)realloc(buf,*n);//空间不足时，重新进行分配
            *(buf+i++)=c;
        }
    }
    *(buf+i++)='\n';
    *(buf+i)='\0';
    return i;

}