#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <time.h>

#define BUFSIZE 1024

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        fprintf(stderr, "Usage...\n");
        exit(1);
    }
    int sd;
    struct sockaddr_in raddr;
    long long stamp;
    char rbuf[BUFSIZE];
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if(sd < 0)
    {
        perror("socket()");
        exit(1);
    }

    raddr.sin_family = AF_INET;
    raddr.sin_port = htons(80);
    inet_pton(AF_INET, argv[1], &raddr.sin_addr);
    if(connect(sd, (void*)&raddr, sizeof(raddr)) < 0)
    {
        perror("connect()");
        exit(1);
    }

    FILE* fp = fdopen(sd, "r+");
    if(fp == NULL)
    {
        perror("fdopen()");
        exit(1);
    }

    fprintf(fp, "GET /tos-cn-i-k3u1fbpfcp/d269a4937bf34f32a5bc56d8b01562cd~tplv-k3u1fbpfcp-zoom-crop-mark:3024:3024:3024:1702.awebp?\r\n\r\n");
    fflush(fp);
    

    FILE* file = fopen("test.awebp", "w");
    int len;
    while(1)
    {
        len = fread(rbuf, 1, BUFSIZE, fp);
        fwrite(rbuf, 1, len, file);
        printf("%d\n", len);
        if(len == 0)
            break;
    }
    
    fclose(fp);

    exit(0);
}