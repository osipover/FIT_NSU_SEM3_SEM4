#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
    printf("PID: %d\n", getpid());
    sleep(10);
    execl("main", " ", NULL);
    printf("Hello world\n");
}

//watch -p -d cat /proc/10302/maps
