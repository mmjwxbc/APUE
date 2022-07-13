#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int i;
    
    // printf("Before while()\n");

    printf("Before while()");
    fflush(NULL);
    while(1);

    printf("After whlie()");

    exit(0);
}