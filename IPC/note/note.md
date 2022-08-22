## 进程间通信
1.  管道
    1.  内核提供、单工、自同步自制（迁就较慢的一方）
    2.  匿名管道
        1.  int pipe(int pipefd[2])
    3.  命名管道
        1.  文件类型为PIPE
        2.  mkfifo()
2.  XSI -> SysV
主动端：先发包的一方
被动端：先收包的一方（先运行）
- Messages Queues 消息队列
  - msgget()
  - msgsnd()
  - msgrcv()
  - msgctl()
- Semaphore Arrays 信号量数组
  - semget()
  - semctl()
- Shared Memory 共享内存段
  - shmget()
- ftok() 使用同一个key值掌握同一个机制
1.  网络套接字socket