#include <stdio.h>
#include <stdlib.h>

int main()
{
    alarm(10);
    alarm(1);
    alarm(5);
    while(1)
        pause();
    exit(0);
}