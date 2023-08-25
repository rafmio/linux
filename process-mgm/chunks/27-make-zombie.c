#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf("process started. Let's call fork()...\n");
    
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork()");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        printf("this is a child process, PID: %d, PPID: %d\n", getpid(), getppid());
        printf("the child proccess will fall asleep to let parent process die and become a zombie...\n\n");
        sleep(3);
   } else {
        printf("this is a child process, PID: %d\n", getpid());
        printf("let the parent process die...\n");
        exit(EXIT_SUCCESS);
    }

    printf("\nthis is a child process, PID: %d, PPID now is: %d\n", getpid(), getppid());
    sleep(2);

    exit(EXIT_SUCCESS);
}