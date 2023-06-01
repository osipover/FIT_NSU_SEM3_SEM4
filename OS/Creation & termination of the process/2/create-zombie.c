#include "zombie.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int create_zombie() {
    printf("pid: %d\n", getpid());

    int pid = fork();

    if (pid == 0) {
        printf("child pid: %d\n", getpid());
        exit(0);
    } else {
        while(1) {}
    }

    return 0;
}
