#include <sys/types.h>
#ifndef _MYPIPE_H__
#define _MYPIPE_H__

#define PIPESIZE 1024
#define MYPIPE_READ 1
#define MYPIPE_WRITE 2
typedef void mypipe_t;

mypipe_t *mypipe_init(void);

int mypipe_register(mypipe_t *, int);

int mypipe_unregister(mypipe_t *, int);

int mypipe_read(mypipe_t *, void *, size_t);

int mypipe_write(mypipe_t *, const void *, size_t);


int mypipe_destory(mypipe_t *);

#endif