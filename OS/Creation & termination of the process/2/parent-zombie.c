#include "zombie.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int make_parent_zombie() {
    printf("pid: %d\n", getpid());
    printf("ppid: %d\n", getppid());

    int child_pid = fork(); 

    if (child_pid == 0) {
        printf("---------pid: %d\n", getpid());
        printf("---------ppid: %d\n", getppid());
      
        int grandchild_pid = fork();
      
        if (grandchild_pid == 0) {
            printf("------------------pid: %d\n", getpid());
            printf("------------------ppid: %d\n", getppid());
            sleep(5);
            printf("------------------ppid: %d\n", getppid());
            while(1) {}
        } else {
            sleep(2);
            exit(0);
        }
    } else {
        while(1) {} 
    }

    return 0;
}
