## 进程标识符pid
- 类型 pid_t
- ps命令
- 进程号顺次向下使用
- getpid()
- getppid()

## 进程的产生
- fork()
  - 同样的进程副本
  - 执行位置一样
  - 父子进程的区别
    - fork返回值不一样
    - pid不同
    - ppid不同
    - 未决信号和文件锁不继承
    - 资源利用率清零
  - init进程
    - pid == 1
    - 所有进程的祖先
  - 调度策略
  - ./fork1 > /tmp/out
    - Begin打印两次?
      - 输出到文件是全缓冲模式 还没来得及输出就fork导致缓冲区出现两份相同的[pid]Begin()!
      - fflush(NULL)
  - 写时拷贝
- vfork()