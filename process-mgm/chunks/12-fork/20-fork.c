#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>

int
main() {
    printf("This is the parent process with process ID: %d\n", getpid());
    printf("Before calling fork()...\n");

    pid_t ret = fork();
    if (ret) {
        printf("The child process is spawned with PID: %d and TID: %d\n", getpid(), gettid());
    } else {
        printf("This is the child process with PID: %d and TID: %d\n", getpid(), gettid());
    }

    printf("Type Ctrl+C to exit...\n");

    while(1);

    return 0;
}