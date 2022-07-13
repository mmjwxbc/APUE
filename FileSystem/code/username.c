#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
int main(int argc, char **argv)
{
    if(argc < 2)
    {
        fprintf(stderr, "Usage...\n");
        exit(1);
    }
    struct passwd *p = getpwuid(atoi(argv[1]));
    puts(p -> pw_name);
    exit(0);
}