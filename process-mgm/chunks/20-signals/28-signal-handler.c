#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_handler(int signum) {
    // return type of the handler function should be void
    printf("\nInside handler function\n");
    printf("the signum is: %d\n", signum);
}

int main() {
    signal(SIGINT, sig_handler);    // Register signal handler
    for (int i = 1; ; i++) {
        printf("%d: Inside main func\n", i);
        sleep(1);
    }

    return 0;
}

// Ctrl + C
// Ctrl + \ 