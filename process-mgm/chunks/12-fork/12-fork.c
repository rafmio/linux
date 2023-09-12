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

    char cmd[] = "ls -la /proc/self/fd";
    printf("cmd: %s\n", cmd);

    int fd = openat(AT_FDCWD, argv[1], O_RDONLY | O_CLOEXEC);
    if (fd == -1) {
        perror("openat()");
        exit(EXIT_FAILURE);
    }

    printf("\nfd directory for PID %d:\n", getpid());
    system(cmd);

    // В дочернем процессе успешный запуск fork() возвращает 0
    // В родительском fork() возвращает pid дочернего
    int newProc = fork();
    printf("Child PID: %d\n", newProc);
    printf("\nfd directory for PID %d:\n", getpid());
    system(cmd);
    printf("\n");

    struct stat statFd;
    int fstatRes = fstat(fd, &statFd);
    if (fstatRes == -1) {
        perror("fstat()");
        return 1;
    }
    printf("st_ino: %ld\n", statFd.st_ino);

    return 0;
}