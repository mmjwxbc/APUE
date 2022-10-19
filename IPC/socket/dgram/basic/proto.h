#include <sys/types.h>
#ifndef PROTO_H
#define PROTO_H

#define RCVPORT "1989"
#define NAMESIZE 11

struct msg_st
{
    uint8_t name[NAMESIZE];
    uint32_t math;
    uint32_t chinese;
}__attribute__((packed));

#endif