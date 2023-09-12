#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t p;
    p = fork();
    if (p == -1) {
        perror("fork()");
        exit(EXIT_FAILURE);
    } else if (p == 0) {
        printf("We are in the child process. PID: %d\n", getpid());
    } else {
        printf("We are in the parent process. PID: %d\n", getpid());
    }

    exit(EXIT_SUCCESS);
}