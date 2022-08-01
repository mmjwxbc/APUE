#ifndef ANYTIMER_H__
#define ANYTIMER_H__

#define JOB_MAX 1024

typedef void at_jobfunc_t(void *);

// 模仿文件描述符
/*
 * return >= 0 成功返回任务ID
 *        == -EINVAL 参数非法
 *        == -ENOSPC 数组满
 *        == -ENOMEM 内存空间不足
 *
 */
int at_addjob(int sec, at_jobfunc_t *jobp, void *arg);

/*
 * return == 0 成功取消
 *        == -EINVAL 参数非法
 *        == -EBUSY 指定任务已完成
 *        == -ECANCELED 指定任务已被取消
 */
int at_canceljob(int id);

/*
 * return == 0 指定任务成功释放
 *        == -EINVAL 参数非法
 */
int at_waitjob(int id);
#endif