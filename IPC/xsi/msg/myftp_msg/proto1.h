#ifndef _PROTO_H__
#define _PROTO_H__

#define KEYPATH "/etc/services"
#define KEYPROJ 'a'
#define PATHMAX 1024
#define DATAMAX 1024

enum
{
    MSG_PATH = 1,
    MSG_DATA,
    MSG_EOF
};

typedef struct msg_path_st
{
    long mytype;
    char path[PATHMAX];
}msg_path_t;

typedef struct msg_data_st
{
    long mytype;
    char data[DATAMAX];
    int datalen;
}msg_data_t;


#endif