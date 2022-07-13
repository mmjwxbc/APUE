#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define TIMESTRSIZE 1024
#define FMTSTRSIZE 1024

extern char *optarg;
extern int optind;

int main(int argc, char *argv[])
{
    time_t stamp;
    struct tm *tm;
    char timestr[TIMESTRSIZE];
    int c;
    char fmtstr[FMTSTRSIZE];
    FILE *fp = stdout;
    fmtstr[0] = '\0';
    while(1)
    {
        c = getopt(argc, argv, "-H:MSy:md");
        if(c < 0)
            break;
        switch(c)
        {
            case 1:
                printf("HHHHHH\n");
                fp = fopen(argv[optind - 1], "w");
                if(fp == NULL)
                {
                    perror("fopen()");
                    fp = stdout;
                }
                break;
            case 'H':
                if(strcmp(optarg, "12") == 0)
                    strncat(fmtstr, "%I(%P) ", FMTSTRSIZE);
                else if(strcmp(optarg, "24") == 0)
                    strncat(fmtstr, "%H ", FMTSTRSIZE);
                else
                    fprintf(stderr, "Invaild argument\n");
                break;
            case 'M':
                strncat(fmtstr, "%M ", FMTSTRSIZE);
                break;
            case 'S':
                strncat(fmtstr, "%S ", FMTSTRSIZE);
                break;
            case 'y':
                if(strcmp(optarg, "2") == 0)
                    strncat(fmtstr, "%y ", FMTSTRSIZE);
                else if(strcmp(optarg, "4") == 0)
                    strncat(fmtstr, "%Y ", FMTSTRSIZE);
                else
                    fprintf(stderr, "Invaild argument\n");
                break;
            case 'm':
                strncat(fmtstr, "%m ", FMTSTRSIZE);
                break;
            case 'd':
                strncat(fmtstr, "%d ", FMTSTRSIZE);
                break;
            default:
                break;
        }
    }
    stamp = time(NULL);
    tm = localtime(&stamp);
    strftime(timestr, TIMESTRSIZE, fmtstr, tm);
    fputs(timestr, fp);
    puts("");
    exit(0);
}

/*
 * -y year
 * -m month
 * -d day
 */