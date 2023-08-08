#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    printf("current PID: %d\n", getpid());
    int a, b, c;
    a = fork();
    b = fork();
    c = fork();

    printf("\nHello-mello, Huggy-Wuggu\n");
    
    printf("a: %d, b: %d, c: %d\n", a, b, c);
    sleep(1);
    return 0;
}

/*
The number of times 'Hello-mello...' is printed is equal to the number of processes
created.
Total number processes = 2n(in n power), where is n is number of fork system calls.
*/