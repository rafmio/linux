#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void funcForChild(pid_t pid);

int main() {
    if ( fork() == 0 ) {
        printf("HC: hello from child\n");
        funcForChild(getpid());
    } else {
        printf("HP: hello from parent\n");
        printf("The PID of parent: %d\n", getpid());
        wait(NULL);
        printf("CT: child has terminated\n");
    }

    printf("Bye, yopta, this was sent by: %d\n", getpid());

    return 0;
}

void funcForChild(pid_t pid) {
    printf("\n\nThis is child proccess, pid: %d, PID(getpid()): %d, PPID: %d\n\n", pid, getpid(), getppid());
}