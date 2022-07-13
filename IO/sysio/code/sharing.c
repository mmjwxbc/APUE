#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: ./sharing <file_name>");
        exit(1);
    }
    FILE* fr = fopen(argv[1], "r");
    if(fr == NULL)
    {
        perror("open()");
        exit(1);
    }
    FILE* fw = fopen(argv[1], "r+");
    int enter_cnt = 0;
    char ch;
    while((ch = fgetc(fr)) != EOF && enter_cnt != 11)
    {
        if(ch == '\n') enter_cnt ++;
    }
    enter_cnt = 0;
    while((ch = fgetc(fw)) != EOF && enter_cnt != 10)
    {
        if(ch == '\n') enter_cnt ++;
    }
    while ((ch = fgetc(fr)) != EOF)
    {
        fputc(ch, fw);
    }
    long offlen = ftell(fw);
    int fd = fileno(fw);
    ftruncate(fd, offlen);
    exit(0);
}