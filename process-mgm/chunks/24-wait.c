#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void waitexample() {
    int stat;
    if ( fork() == 0 ) {
        printf("child proc with PID %d and PPID %d will be exit\n", getpid(), getppid());
        exit(EXIT_FAILURE);
    } else {
        printf("The parent proc with PID %d will be waiting...\n", getpid());
        wait(&stat);
    }

    if (WIFEXITED(stat))
        printf("Exit status: %d\n", WEXITSTATUS(stat));
    else if (WIFSIGNALED(stat))
        psignal(WTERMSIG(stat), "Exit signal");
}

int main() {
    waitexample();

    return 0;
}