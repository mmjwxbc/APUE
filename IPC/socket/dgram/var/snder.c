#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include "proto.h"
#define IPSTRSIZE 40
int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        fprintf(stderr, "Usage: ./snder\n");
        exit(1);
    }
    if(strlen(argv[2]) > NAMEMAX)
    {
        fprintf(stderr, "Name is too long!\n");
        exit(1);
    }
    int sd, size;
    struct msg_st *sbufp;
    struct sockaddr_in raddr;
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sd < 0)
    {
        perror("socket()");
        exit(1);
    }
    size = sizeof(struct msg_st) + strlen(argv[2]) - 1;
    sbufp = malloc(size);
    if(sbufp == NULL)
    {
        perror("malloc");
        exit(1);
    }
    strcpy(sbufp->name, argv[2]);
    sbufp->math = htonl(rand() % 100);
    sbufp->chinese = htonl(rand() % 100);

    raddr.sin_family = AF_INET;
    raddr.sin_port = htons((atoi(RCVPORT)));
    inet_pton(AF_INET, argv[1], &raddr.sin_addr);
    if(sendto(sd, sbufp, size, 0, (void*) &raddr, sizeof(raddr)) < 0)
    {
        perror("sendto");
        exit(1);
    }

    puts("OK");

    close(sd);

    exit(0);
}