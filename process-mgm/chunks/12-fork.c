#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Too few arguments. Usage: %s <fileName>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char cmd[] = "ls -la ";
    char pid[] = "";
    sprintf(pid, "%d", getpid);
    strcat(cmd, "/proc/"); 
    strcat(cmd, pid);
    strcat(cmd, "/fd");
    printf("cmd: %s\n", cmd);

    int fd = openat(AT_FDCWD, argv[1], O_RDONLY | O_CLOEXEC);
    if (fd == -1) {
        perror("openat()");
        exit(EXIT_FAILURE);
    }

    system(cmd);
}