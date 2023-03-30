#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
        pid_t pid = fork();

        if (pid == 0) {
                ptrace(PTRACE_TRACEME, 0, 0, 0);
		            execl("hello", " ", NULL);
        }
  
        int status = 0;
        wait(&status);

        while (!WIFEXITED(status)){
                ptrace(PTRACE_SYSCALL, pid, 0, 0);
                wait(&status);
                if (WIFSTOPPED(status)) {
                        struct user_regs_struct state;
                        ptrace(PTRACE_GETREGS, pid, 0, &state);
                        int syscallId = state.orig_rax;
                        printf("SYSCALL: %d\n", syscallId);
                }
        }
}   
