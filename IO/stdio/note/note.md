IO是实现一切的基础
## stdio
- error
  - 不再是全局变量，被私有化，错误映射到出错进程的内存空间当中
- 文件权限
  - 0666 & ~umask(0002)
  - 0666    000 110 110 110
  - umask   000 000 000 010
  - ~umask  111 111 111 101
- FILE *fopen(const char *path, consr char *mode)
  - FILE结构体存在位置
    - 堆(T)
    - 栈(F)
    - 静态区(F)
- int fclose(FILE *fp)
- 字符相关
  - int fgetc(FILE *stream)   函数形式
    - int getc(FILE *stream) define形式
  - int fputc(int c, FILE *stream)
- 字符串相关
  - char *gets(char *s)
    - 不检查缓冲区溢出
  - fgets(char *s, int size, FILE *stream)
  - fputs(const char *s, FILE *stream)
- fread()
- fwrite()

- printf()
  - fprintf()
    - 输出重定向
  - sprintf()
    - 类似于itoa
  - snprintf()
- scanf()
  - fscanf()
  - sscanf()

- 操作文件位置指针
  - function
    - reposition a stream
  - fseek(FILE *stream, long offset, int whence)
    - 定位 
  - ftell()
    - 当前文件指针位置
  - rewind()
    - 重置当前位置指针为零

- fflush()
  - 刷新缓冲区
  - 解决行缓冲
- 缓冲区
  - 合并系统调用
  - 分类
    - 全缓冲：我们缓存在缓冲区的东西在缓冲区满的时候，才写入磁盘或者我们调用fflush刷新缓冲区才能写入到磁盘。对于全缓冲，如果我们缓冲区没满，或者我们没有手动刷新缓存，那么缓存区的内容是不能写入到磁盘的
    - 行缓冲：我们标准输入、标准输出都是采用的行缓存，也就是遇到换行符的时候，才会将缓存区的东西写入到磁盘
    - 无缓存：有的时候，我们希望一些内容在第一时间写入磁盘或者显示出来，比如我们显示错误信息的时候，这时候典型的例子比如标准出错，它就是直接显示出错信息，而不会先放入缓存

- getline()
  - 实现原理
    - 函数封装
      - malloc  
      - realloc

- 临时文件
  - char tmpnam(char *s)
  - FILE *-tmpfile(void)
  - 没有指向的时候，自动销毁