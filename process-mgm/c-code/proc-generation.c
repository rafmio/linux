#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {
    int pid;
    int status, died;

    pid = fork();
    switch(pid) {
        case -1: 
            printf("can't fork\n");
            exit(-1);
        case 0:
            printf("I'm the child of PID %d\n", getpid());
            printf("My PID is %d\n", getpid());

            sleep(2); // waiting for 2 seconds
            exit(0);
        default:
            printf("I'm the parent\n");
            printf("My PID is %d\n", getpid());

            sleep(5);
            if (pid & 1)
                kill(pid, SIGKILL);
            died = wait(&status);
            printf("value of died: %d\n", died);


    }
}
