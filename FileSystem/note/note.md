- 创建-a文件
  - touch --(代表选项结束) -a
  - touch ./-a
## 目录和文件 
### 获取文件属性
- stat()
  - 通过文件路径获取属性 面对符号链接文件时获取的是所指向的目标文件的属性
- fstat()
  - 面对文件描述符获取属性
- lstat()
  - 面对符号链接文件时获取的是符号链接文件的属性

- 空洞文件
- st_mode
  - 文件类型
    - dcb-lsp
      - 目录
      - 字符设备
      - 块设备
      - 常规文件
      - 符号链接文件
      - socket文件
      - 管道文件
  - 文件属性

### 文件访问权限
st_mode是16位的位图

### umask
防止产生权限过松的文件

### 文件权限的管理
chmod(const char *path, mode_t)
fchmod(int fd, mode_t mode)

### 粘住位
t位
- 如果在一个执行文件设置了该位，则执行该文件且进程结束后，系统会把该进程的正文部分放置磁盘的交换区中，在交换区中文件是连续存放的，不像非交换区一样，一个文件的内容分散在磁盘的几个块中。所以在加载该执行文件时就可以加快速度启动，直接从交换区中把进程的正文部分取至内存中运行

### 文件系统
文件或数据的存储和管理
- FAT
- UFS

### 硬链接 符号链接
- 硬链接
  - 与目录项是同义词
  - 不能建立分区或者目录硬链接
- 符号链接
  - 可跨分区 可目录
  - 类似于Windows的快捷方式
  - 文件大小即为所指向文件名字符数组长度
  - 属性存储在inode不在磁盘块当中
- rename()
- unlink()
- link()
- remove()

### 目录创建和销毁

- mkdir()
- rmdir()
  - 仅删除空目录
  - 非空目录只能递归删除

### 更改当前目录路径
- chdir()
- fchdir()
- getcwd()
  - 获取当前工作路径

### 分析目录、读取目录内容
- glob()
  - 解析模式串
- opendir()
- closedir()
- readdir()
- rewinddir()
- seekdir()
- telldir()

## 系统数据文件和信息
- /etc/passwd
  - getpwiud()
  - getpwnam()
- /etc/group
  - getgruid()
  - getgrnam()
- /etc/shadow
  - getspnam()
  - crypt() 加密
  - getpass() 关闭回显功能
- 时间戳
  - time()
    - 返回以秒为单位的整数
  - gmtime()
  - localtime()
  - mktime()
  - strftime()

## 进程环境
- main()
- 进程的终止
  - 正常终止
    - 从main()函数返回
    - 调用exit
    - 调用_exit()或_Exit
      - 直接推退出，不执行钩子函数
    - 最后一个线程从其启动例程返回
    - 最后一个线程调用pthread_exit()
  - 异常终止
    - 调用abort
    - 接到信号并终止
    - 最后一个线程对其取消请求作出响应
  - atexit()
    - 钩子函数
    - register a function to be called at normal process termination
- 命令行参数
  - getopt()

- 环境变量
  - KEY = VALUE
  - getenv()
  - setenv()
  - putenv()

- C程序空间布局
  - pmap()
- 库
  - 静态库
  - 动态库
  - 手工装载库(库打桩)
    - dlopen()
    - dlclose()
    - dlerror()

- 函数跳转
  - 跨函数跳转
  - setjmp()
  - longjmp()

- 资源的获取和控制
  - getrlimit()
  - setrlimit()