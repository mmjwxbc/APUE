#include <stdio.h>
#include <stdlib.h>
#include <shadow.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    struct spwd *shadowline;
    if(argc < 2)
    {
        fprintf(stderr, "Usage...\n");
        exit(1);
    }
    char *input_pass = getpass("Password:");
    shadowline = getspnam(argv[1]);
    char *crypt_pass = (input_pass, shadowline -> sp_pwdp);
    if(strcmp(shadowline -> sp_pwdp, crypt_pass) == 0)
        puts("OK");
    else puts("Failed");
    exit(0);
}