#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sig_handler(int signum) {
    printf("\nInside handler func. The signum is: %d\n", signum);
    signal(SIGINT, SIG_DFL);        // Re-register signal hanlder for default action
}

int main() {
    signal(SIGINT, sig_handler);    // Register signal handler
    for (int i = 1; ; i++) {        // Infinite loop
        printf("%d : Inside main func\n", i);
        sleep(1);
    }
}