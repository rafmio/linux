#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Too few arguments. Usage: '$ %s <PID>", argv[0]);
    }

    pid_t pid = atof(argv[1]);
    printf("Let's we check background processes:\n");
    system("jobs -l");
    printf("Let's send kill to PID %d...\n", pid);

    printf("command 'jobs -l' now is...\n");

    int killRes = kill(pid, SIGKILL);
    if (killRes == -1) {
       perror("kill():");
       exit(EXIT_FAILURE);
    }
    system("jobs -l"); // ничего не выведет, будет пустота

    exit(EXIT_SUCCESS);
}