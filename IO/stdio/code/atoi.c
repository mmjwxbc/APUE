#include <stdio.h>
#include <stdlib.h>

int main()
{
    // char str[] = "123456";
    // printf("%d\n", atoi(str));
    char buf[1024];
    int year = 2022, month = 7, day = 1;
    sprintf(buf, "%d-%d-%d", year, month, day);
    puts(buf);
    exit(0);
}