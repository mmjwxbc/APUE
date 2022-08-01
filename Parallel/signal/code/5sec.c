#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
int main()
{
    time_t end;
    size_t cnt = 0;
    end = time(NULL) + 5;
    while(time(NULL) <= end)
    {
        cnt ++;
    }
    printf("%ld\n", cnt);
    exit(0);
}