#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/select.h>
#define TTY1 "/dev/tty10"
#define TTY2 "/dev/tty11"
#define BUFSIZE 1024
enum
{
    STATE_R = 1,
    STATE_W,
    STATE_Ex,
    STATE_T
};

struct fsm_st
{
    int state;
    int sfd;
    int dfd;
    int len;
    int pos;
    char *errstr;
    char buf[BUFSIZE];
};

static void fsm_driver(struct fsm_st *fsm) 
{
    int ret;
    switch(fsm->state)
    {
        case STATE_R:
            fsm->len = read(fsm->sfd, fsm->buf, BUFSIZE);
            if(fsm->len == 0)
                fsm->state = STATE_T;
            else if(fsm->len < 0){
                if(errno == EAGAIN) {
                    fsm->state = STATE_R;
                }
                else {
                    fsm->state = STATE_T;
                    fsm->errstr = "read()";
                }
            }
            else {
                fsm->pos = 0;
                fsm->state = STATE_W;
            }
            break;
        case STATE_W:
            ret = write(fsm->dfd, fsm->buf + fsm->pos, fsm->len);
            if(ret < 0) {
                if(errno == EAGAIN) {
                    fsm->state = STATE_W;
                } else {
                    fsm->state = STATE_Ex;
                    fsm->errstr = "write()";
                }
            } else {
                fsm->pos += ret;
                fsm->len -= ret;
                if(fsm->len == 0)
                    fsm->state = STATE_R;
                else
                    fsm->state = STATE_W;
            }
            break;
        case STATE_Ex:
            perror(fsm->errstr);
            fsm->state = STATE_T;
            break;
        case STATE_T:
            abort();
            break;
    }
}
int max(int fd1, int fd2)
{
    return fd1 > fd2 ? fd1 : fd2;
}
void relay(int fd1, int fd2)
{
    fd_set rset, wset;
    int fd1_save, fd2_save;
    struct fsm_st fsm12, fsm21;
    fd1_save = fcntl(fd1, F_GETFL);
    fcntl(fd1, F_SETFL, fd1_save | O_NONBLOCK);
    fd2_save = fcntl(fd2, F_GETFL); // 获取文件状态
    fcntl(fd2, F_SETFL, fd2_save | O_NONBLOCK);

    fsm12.state = STATE_R;
    fsm12.sfd = fd1;
    fsm12.dfd = fd2;

    fsm21.state = STATE_R;
    fsm21.sfd = fd2;
    fsm21.dfd = fd1;

    while(fsm12.state != STATE_T || fsm21.state != STATE_T)
    {
        FD_ZERO(&rset);
        FD_ZERO(&wset);

        if(fsm12.state == STATE_R) 
            FD_SET(fsm12.sfd, &rset);
        if(fsm12.state == STATE_W)
            FD_SET(fsm12.dfd, &wset);
        if(fsm21.state == STATE_R) 
            FD_SET(fsm21.sfd, &rset);
        if(fsm21.state == STATE_W)
            FD_SET(fsm21.dfd, &wset);
        if(select(max(fd1, fd2) + 1, &rset, &wset, NULL, NULL) < 0) {
            if(errno == EINTR)
                continue;
            perror("select()");
            exit(1);
        }
        if(FD_ISSET(fd1, &rset) || FD_ISSET(fd2, &wset))
            fsm_driver(&fsm12);
        if(FD_ISSET(fd1, &rset) || FD_ISSET(fd2, &wset))
            fsm_driver(&fsm21);
    }

    fcntl(fd1, F_SETFL, fd1_save);
    fcntl(fd2, F_SETFL, fd2_save);
}

int main()
{
    int fd1, fd2;
    fd1 = open(TTY1, O_RDWR);
    if(fd1 < 0) {
        perror("open()");
        exit(1);
    }
    write(fd1, "TTY1", 5);
    fd2 = open(TTY2, O_RDWR | O_NONBLOCK);
    if(fd2 < 0) {
        perror("open()");
        exit(1);
    }
    write(fd2, "TTY2", 5);
    relay(fd1, fd2);
    close(fd1);
    close(fd2);
    exit(0);
}
