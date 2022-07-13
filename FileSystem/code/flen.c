#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: ./flen <file_name>\n");
        exit(1);
    }
    struct stat statbuf;
    int ret = stat(argv[1], &statbuf);
    if(ret < 0)
    {
        perror("stat()");
        exit(1);
    }
    printf("size = %ld\n", statbuf.st_size);
    exit(0);
}