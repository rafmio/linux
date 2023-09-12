#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void forkeExample() {
    if (fork() == 0) {
        printf("Hello from Child!\n");
    } else {
        printf("Hello form Parent!\n");
    }
}

int main() {
    forkeExample();
    return 0;
}