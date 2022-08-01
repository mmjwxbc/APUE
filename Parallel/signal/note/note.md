- 同步
- 异步
  - 例子:俄罗斯方块
  - 事件到达时间未知 产生结果未知
  - 处理方法
    - 查询法
    - 通知法
## 信号
### 信号的概念
- 信号是软件中断
- 信号的响应依赖于中断
- core文件
  - ulimit
### signal
- typedef void (*sighandler_t)(int);
  - 返回值为void
  - 参数为int类型
- signal(int signum, sighandler_t handler);
- 信号会打断阻塞的系统调用
  - sleep

### 信号的不可靠
- 信号的行为不可靠
- 执行现场由内核产生
  - 多次信号会重置当前现场
- 在单任务或单线程且没有中断的系统中，程序是顺序执行的，就不存在可重入性的问题,而在多任务或多线程的系统中，多任务可以同时调用一函数，即正在执行的函数可能被打断,如果能够保证打断后，继续执行的结果与未被打断执行的结果保持一致，函数即具有可重入性
### 可重入函数
- 解决信号不可靠问题
- 所有的系统调用都是可重入的
- 部分库函数也是可重入
  - memcpy

### 信号的响应过程
- mash位图
- pending位图
- 信号从收到到响应有不可避免的延迟
- 标准信号响应没有严格的顺序
- 标准信号为什么会丢失
  - 位图不记录信号到来次数
- 如何忽略信号
  - 将响应的mash位置为0

### 常用函数
- kill()
  - 给进程发信号
- raise()
  - 给自己发信号
- alarm()
- pause()
  - 等待信号打断进程
- setitimer()
```c
// 参考知乎: https://zhuanlan.zhihu.com/p/343124524
#include<sys/time.h>
int setitimer(int which,const struct itimerval *new_value, struct itimerval *old_value);
/*
功能   设置定时器，可代替alarm，精度可到微秒，可以实现周期定时
参数   which 定时方式
             自然定时  ITIMER_REAL(14)  SIGALRM 计算自然时间
             虚拟空间计时(用户空间)  ITIMER_VIRTUAL(26)   SIGVTALRM 只计算进程占用CPU的时间
             运行时计时(用户+内核)   ITIMER_PROF(27)  SIGPROF 计算占用CPU及执行系统调用的时间

       new_value  struct itimerval   负责设定 timout 时间
                  struct itimerval{
                      struct  timerval it_interval;  // 闹钟触发周期
                      struct  timerval it_value;     // 闹钟触发时间
                  };
                  struct timerval{
                      long tv_sec;           // 秒
                      long tv_usec;          // 微秒
                  };

                  itimerval.it_value          // 第一次执行 function 所延迟的秒数
                  itimerval.it_interval       // 每隔几秒执行 function
        
       old_value  存放旧的timeout值，一般指定为NULL

返回值  成功 0    失败 -1

*/




// setitimer1.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<signal.h>

void func1(int no){
	printf("func1 %d\n",no);

}


int main(){

	struct itimerval tmo;
	
	//第一次触发时间
	tmo.it_value.tv_sec=3;
	tmo.it_value.tv_usec=0;

	//后面的周期性触发
	tmo.it_interval.tv_sec=2;
	tmo.it_interval.tv_usec=0;


	//设置定时器
	setitimer(ITIMER_REAL,&tmo,NULL);
	

	//捕捉信号 SIGALRM
	signal(SIGALRM,func1);
	
	while(1){}
	
	return 0;
}

// 编译 gcc setitimer1.c -o setitimer1
// 运行 ./setitimer1   结果如下图   除第一次外，后面每2S被捕捉一次
```
- abort()
  - 杀掉进程得到线程现场报告
- system()
- sleep()
- usleep()