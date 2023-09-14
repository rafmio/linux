#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sig_handler(int signum) {
    printf("Inside handler function. The signum : %d\n", signum);
}

int main() {
    signal(SIGALRM, sig_handler);       // register signal hanlder
    alarm(4);   // scheduled alarm after 4 seconds
    alarm(1);   // scheduled alarm after 1 second

    for (int i = 1; ; i++) {
        printf("%d : Inside main function\n", i);
        sleep(1);
    }

    return 0;
}

/* Generating SIGALRM using signal() function cannot be stacked. 
Only one SIGALRM generation can be scheduled. Successive calls of signal() 
function reset the alarm clock of the calling process */