#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    char *args[] = {"ls", "-l", "/proc/self/fd"};
    int ret = execl("/bin/ls", args[0], args[1], args[2], NULL);
    if (ret == -1) {
        perror("execl");
        _exit(EXIT_FAILURE);
    }

    _exit(EXIT_SUCCESS);
}