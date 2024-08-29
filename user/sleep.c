#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    if(argc < 2){
        printf("Usage: sleep seconds\n");
        exit(0);
    }

    int ticks = atoi(argv[1]);
    if (ticks <= 0) {
        printf("Invalid time: %s\n", argv[1]);
        exit(0);
    }

    sleep(ticks);

    exit(0);
}
