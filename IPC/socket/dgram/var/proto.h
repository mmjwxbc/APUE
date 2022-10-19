#include <sys/types.h>
#ifndef PROTO_H
#define PROTO_H

#define RCVPORT "1989"
#define NAMEMAX 512 - 8 - 8

struct msg_st
{
    uint32_t chinese;
    uint32_t math;
    uint8_t name[NAMEMAX];
}__attribute__((packed));

#endif