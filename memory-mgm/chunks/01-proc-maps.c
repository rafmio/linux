#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int
main(void) {
    int fd;
    int pid;
    char pidStr[64];

    char filename[] = "maps";
    pid = getpid();
    snprintf(pidStr, 64)
    fd = openat()
}