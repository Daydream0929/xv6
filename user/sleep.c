#include "kernel/types.h"
#include "user/user.h"

int 
main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(2, "please enter sleep <time>\n");
        exit(1);
    } else {
        int t = atoi(argv[1]);
        sleep(t);
    }
    exit(0);
}
