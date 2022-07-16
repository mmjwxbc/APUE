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


## 进程的消亡及释放资源
- wait()
- waitpid()
- waitid()
- wait3()
- wait4()

## exec函数族
- execl()
- execlp()
- execle()
- execv()
- execvp()
## 用户权限和组权限
- r
- e
- s
- 文件属性u + s
  - 拥有该文件user用户的权限
- getuid()
- geteuid()
- getgid()
- getegid()
- setuid()
  - 设置effective id
- setgid()
- setreuid()
- setregid()
- seteuid()
- setegid()

## 解释器文件
- 脚本文件
  - 装载可执行二进制程序
  - 加载shell程序执行命令

## system
- execute a shell command
- 约等于fork exec wait的封装

## 进程会计
- acct()

## 进程时间
- times()