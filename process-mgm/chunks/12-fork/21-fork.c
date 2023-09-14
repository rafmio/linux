#include <stdio.h>
#include <unistd.h>

int
main() {
    pid_t ret = fork();
    if(ret) {
        for (size_t i = 0; i < 5; i++) {
            printf("AAA\n");
            usleep(1);
        }
    } else {
        for (size_t i = 0; i < 5; i++) {
            printf("BBBBBB\n");
            usleep(1);
        }
    }

    return 0;
}