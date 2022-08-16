## 线程


### 线程的概念
- 广义：一个正在运行的函数。 \
- POSIX是线程标准。
-准确定义：线程（英语：thread）是操作系统能够进行运算调度的最小单位。它被包含在进程之中，是进程中的实际运作单位。一条线程指的是进程中一个单一顺序的控制流，一个进程中可以并发多个线程，每条线程并行执行不同的任务。在Unix System V及SunOS中也被称为轻量进程（lightweight processes），但轻量进程更多指内核线程（kernel thread），而把用户线程（user thread）称为线程。
- 线程标识：pthread_t
- pthread_equal()：比较两个线程号。相等返回非零，否则返回零
- pthread_self()：获取当前线程的标识
### 线程的创建
- pthread_create()：创建一个线程
  - pthread_t *thread 回填指针
  - const pthread_attr_t *attr 指定线程属性
  - void *(*start_routine) (void *) 函数指针 
  - void *arg 调用函数的参数
  - 创建成功返回零，否则返回error number
- 线程的调度取决于调度器策略案例 ../code/posix/create1.c

### 线程终止
1.  线程从启动例程返回，返回值就是线程的退出码
2.  线程可以被同一进程中的其他线程取消
3.  线程调用pthread_exit()函数
- pthread_exit()
- pthread_join()：类似于进程当中的wait()
  - pthread_t thread 指定等待（收尸）的线程
  - void **retval 
### 栈的清理
栈空间大小决定一个进程可以创建的线程个数
- pthread_cleanup_push() 宏定义
- pthread_cleanup_pop() 宏定义 gcc %.c -E查看
### 线程的取消选项
- pthread_cancel(pthread_t pthread)
- 场景：二叉树查找，每棵树一个线程查找，当一个线程找到后，应取消其他线程
- 取消2种状态：允许和不允许
  - 允许取消分为：异步cancel，推迟cancel（默认）-> 推迟到cancel点再响应
  - cancel点：POSIX定义的cancel点，都是可能发送阻塞的系统调用
  - pthread_setcancelstate()：设置是否允许取消
  - pthread_setcanceltype()：设置取消方式
  - pthread_testcancel()：取消点
### 线程分离
- pthread_detach()：分离后不能再操纵该线程
### 线程同步
互斥量：
- pthread_mutex_init()
- pthread_mutex_destory()
- pthread_mutex_lock() 死等状态                                              
- pthread_mutex_unlock() 
条件变量：
- pthread_cond_init()
- pthread_cond_destory()
- pthread_cond_broadcast()
- pthread_cond_signal()


信号量 \
读写锁：读锁->共享锁 写锁->互斥锁
### 线程属性
pthread_attr_t
- pthread_attr_init()
- pthread_attr_destory()

- pthread_attr
### 线程同步的属性
互斥量属性：
- pthread_mutexattr_init();
- pthread_mutexattr_getpshared(); 跨进程使用
- pthread_mutexattr_setpshared();
- pthread_mutexattr_settype();

### 重入、线程和信号的关系、线程与fork