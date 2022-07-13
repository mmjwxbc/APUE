#include <stdio.h>
#include <stdlib.h>
extern char **environ;
int main(int argc, char **argv)
{
    puts(getenv("PATH"));
    getchar();
    exit(0);
}