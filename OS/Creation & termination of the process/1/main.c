#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int global_init = 10;

void show_addresses(int* ptr_local_init) {
    printf("&local_init = %p\n", ptr_local_init);
    printf("&global_init = %p\n\n", &global_init);
}

void show_pid() {
    printf("PID:%d\n", getpid());
}

void show_values(int local_init) {
    printf("local_init = %d\n", local_init);
    printf("global_init = %d\n\n", global_init);
}

int main(int argc, char** argv) {
    int local_init = 20;

    show_address(&local_init);
    
    printf("pid:%d\n", getpid());

    int pid = fork();

    if (pid == 0) {
        printf("------------------- CHILD PROC -------------------\n\n");
        int parent_pid = getppid();
        int child_pid = getpid();
        printf("parent pid: %d\n", parent_pid);
        printf("child pid: %d\n\n", child_pid);

        show_addresses(&local_init);

        local_init = 200;
        global_init = 100;

        show_values(local_init);

        printf("--------------------------------------------------\n");

        exit(5);
    } else {
        sleep(3);
        show_values(local_init);
        sleep(30);

        int child_status;
        wait(&child_status);
        printf("Child exit code: %d\n", WEXITSTATUS(child_status));
    }
}
