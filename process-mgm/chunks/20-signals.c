// $ kill -TERM <PID>
// $ kill -KILL <PID>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int signal) {
    if (signal == SIGINT) {
        printf(" : got Ctrl+C signal handled!\n");
    }
}

int
main() {
    int counter = 0;
    char cmd[] = "ping -c 3 www.ya.ru";
    signal(SIGINT, handler);
    while(counter < 10) {
        printf("\ncounter: %d\n", counter);
        system(cmd);
        counter++;
    }

    exit(EXIT_SUCCESS);
}

/*
SIGINT - "interrupt signal", Ctrl+C

sighandler_t signal(int signum, sighandler_t handler);
signal() returns:
    - previous value of the signal handler, or
    - SIG_ERR on error
*/