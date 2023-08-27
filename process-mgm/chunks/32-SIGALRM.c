#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sig_handler (int signum) {
    printf("Inside handler func. Received signum is: %d\n", signum);
}

int main() {
    signal(SIGALRM, sig_handler);   // register signal handler
    alarm(2);                       // scheduled alarm after 2 seconds

    for (int i = 1; ; i++) {
        printf("%d : Inside main function\n", i);
        sleep(1);                   // delay for 1 second
    }

    return 0;
}