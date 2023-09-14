#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sig_handler(int signum) {
    if (signum == SIGALRM) {
        printf("Inside handler function for SIGALRM\n");
        alarm(2);
    }

    if (signum == SIGINT) {
        printf("\nSnoozing for 5 seconds...\n");
        alarm(5);
    }
}

int main() {
    signal(SIGALRM, sig_handler);
    signal(SIGINT,  sig_handler);

    alarm(2);

    for (int i = 1; ; i++) {
        printf("%d : Inside main function\n", i);
        pause();  // syscall pause() waiting for signal
    }

    return 0;
}