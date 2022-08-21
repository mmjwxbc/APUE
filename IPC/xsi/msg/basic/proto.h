#ifndef _PROTO_H__
#define _PROTO_H__

#define KEYPATH "/etc/services"
#define KEYPROJ 'g'
#define NAMESIZE 1024

struct msg_st
{
    char name[NAMESIZE];
    int math;
    int chinese;
};

#endif