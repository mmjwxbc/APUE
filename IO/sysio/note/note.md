## sysio

- 文件描述符
  - 实质是整型数
    - 数组下标
    - 数组元素是指向某结构体的指针
  - 磁盘上的文件由inode唯一标识
  - 优先使用当前可用范围最小的
  - 存在于进程空间
    - 进程特有
  - 一个fd对应一个结构体
### 文件IO操作
- int open(const char *patname, int flags, [mode_t mode])
  - O_CREAT必须选择三参形式 因为要指定权限
  - C语言没有重载 用的是变参
- close(int fd)
- ssize_t read(int fd, void *buf, size_t count)
- ssize_t write(int fd, const void *buf, size_t count)
- off_t lseek(int fd, off_t offset, int whence)

### sysio 和 stdio 的区别
- sysio 响应快
- stdio 吞吐量大
- 两者不能混用
  - 存在缓冲区 导致文件位置指针不一致
- 转换
  - fdopen()
  - fileno()
- exp
  - ab.c
### IO效率问题
BUFSIZE
  1024    real    0m30.332s
          user    0m1.556s
          sys     0m27.560s
  2048    real    0m8.909s
          user    0m0.761s
          sys     0m6.919s
  4096    real    0m5.039s
          user    0m0.373s
          sys     0m4.148s
  8192    real    0m3.757s
          user    0m0.186s
          sys     0m2.973s
  16384   real    0m3.437s
          user    0m0.112s
          sys     0m3.032s
  32768   real    0m3.120s
          user    0m0.073s
          sys     0m2.711s
  65536   real    0m2.768s
          user    0m0.038s
          sys     0m2.358s
  131072  real    0m2.279s
          user    0m0.021s
          sys     0m1.889s
  262144  real    0m2.276s
          user    0m0.013s
          sys     0m1.886s
  524288  real    0m2.560s
          user    0m0.004s
          sys     0m2.185s
### 文件共享
- 多个任务共同操作一个文件或者协同完成任务

### 原子操作
- 不可分割的操作
- 作用
  - 解决竞争和操作

### 程序中的重定向
复制文件描述符
- dup()
- dup2()

### 同步
- sync()
- fsync()
- fdatasync()

- 管家级别的函数
  - fcntl()
    - 文件相关的内容
  - ioctl()
    - 设备相关的内容

- /dev/fd
  - 虚目录 显示当前进程的文件描述符信息