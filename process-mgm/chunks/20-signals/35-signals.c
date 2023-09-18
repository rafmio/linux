#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void
handle_user_signals(int signal) {
    switch(signal) {
        case SIGUSR1:
            printf("SIGUSR1 received\n");
            break;
        case SIGUSR2:
            printf("SIGUSR2 received\n");
            break;
        default:
            printf("Unsupported signal is received\n");
    }
}

void
handle_sigint(/*int signal*/) {
    printf("Interrupt signal is received\n");
}

void 
hanlde_sigkill(/*int signal*/) {
    printf("Kill signal is received. Bye!\n");
    exit(0);
}

int
main() {
    signal(SIGUSR1, handle_user_signals);
    signal(SIGUSR2, handle_user_signals);
    signal(SIGINT,  handle_sigint);
    signal(SIGKILL, hanlde_sigkill);
    while (1);

    return 0;
}

/*
$ gcc -Wall -Wextra -Werror 35-signal.c -o 35-signal.out
$ ./35-signal.out
$ ctrl+z - чтобы посмотреть PID

Можно из другого терминала:
$ kill -SIGUSR2 <PID>
$ kill -SIGUSR1 <PID>
$ kill -SIGINT <PID>
$ kill -SIGKILL <PID>
*/