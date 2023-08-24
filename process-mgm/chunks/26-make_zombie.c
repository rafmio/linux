#include <signal.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CMD_SIZE 256

int
main(int argc, char *argv[]) {
    printf("argc: %d, argv: %s\n", argc, argv[0]);

    char cmd[CMD_SIZE];
    pid_t childPid;

    setbuf(stdout, NULL);   // Отключаем буферизацию stdout

    switch (childPid = fork()) {
        case -1:
            perror("fork()");
            exit(EXIT_FAILURE);
        case 0:             // Потомок немедленно завершается, чтобы стать зомби
            printf("Child (PID=%ld) exiting\n", (long)getpid());
            _exit(EXIT_SUCCESS);
        default:            // Родитель
            sleep(3);       // Даем потомку шанс начать выполнение и завершиться
            // snprintf(cmd, CMD_SIZE, "ps | grep %s", basename(argv[0]));
            snprintf(cmd, CMD_SIZE, "ps");
            system(cmd);

            // Теперь отправляем зомби сигнал о безусловном завершении

            if ( kill(childPid, SIGKILL) == -1 ) {
                perror("kill()");
                exit(EXIT_FAILURE);
            }

            sleep(3);       // Даем потомку шанс отреагировать на сигнал
            printf("\nAfter sending SIGKILL to zombie (PID=%ld):\n", (long) childPid);
            printf("\n");
            system(cmd);    // Опять видим потомка - зомби

            exit(EXIT_SUCCESS);
    }
}