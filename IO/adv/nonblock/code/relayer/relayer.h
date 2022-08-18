#include <stdint.h>
#ifndef RELAYER_H__
#define RELAYER_H__

#define REL_JOBMAX 10000

enum
{
    STATE_RUNNING = 1,
    STATE_CANCELED,
    STATE_OVER
};
struct rel_stat_st
{
    int state;
    int fd1;
    int fd2;
    int64_t count12, count21;
};

int rel_addjob(int fd1, int fd2);
/*
 * return >= 0 success, return job_id
 *        == -EINVAL    failure invaild argumment
 *        == -ENOSPC    failure no space
 *        == -ENOMEN    failure no memory
 * */
int rel_canceljob(int id);

/*
 * return == 0 success, cancel job sucessfully
 *        == -EINVAL    failure invaild argumment
 *        == -EBUSY     failure job had been canceled
 * */
int rel_waitjob(int id, struct rel_stat_st *);

/*
 * return == 0 success, job had been stop, return status
 *        == -EINVAL    failure invaild argumment
 * */

int rel_statjob(int id, struct rel_stat_st *);

/*
 * return == 0 success, return status
 *        == -EINVAL    failure invaild argumment
 * */
#endif