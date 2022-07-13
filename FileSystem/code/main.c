#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    // ./main *.c ouput 5 shell会解析模式
    printf("argv = %d\n", argv);
    exit(0);
}