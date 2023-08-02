#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int
main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Too few arguments. Usage: %s <fileName>\n", argv[0]);
        _exit(EXIT_FAILURE);
    }
    printf("buplicate an existing fd (F_DUPFD) %d\n", F_DUPFD);
    printf("get fd flags (F_GETFD) %d\n", F_GETFD);
    printf("set fd flags (F_SETFD) %d\n", F_SETFL);
    printf("get file status flags (F_GETFL) %d\n", F_GETFL);
    printf("set file status flags (F_SETFL) %d\n", F_SETFL);
    printf("get record locks (F_GETLK) %d\n", F_GETLK);
    printf("set record locks (F_SETLK) %d\n", F_SETLK);
    printf("get asynchronous I/O ownership (F_GETOWN) %d\n", F_GETOWN);
    printf("set asynchronous I/O ownership (F_SETOWN) %d\n", F_SETOWN);
    printf("\n");

    int fd = openat(AT_FDCWD, argv[1], O_RDONLY | O_CLOEXEC);
    if (fd == -1) {
        perror("openat()");
        _exit(EXIT_FAILURE);
    }

    int flags = fcntl(fd, F_GETFL);
    if (flags < 0) {
        perror("fcntl()");
        _exit(EXIT_FAILURE);
    } else {
        printf("File status flags retrieved. flags: %d\n", flags);
    }

    // Проверить установлены ли O_RDONLY, O_WRONLY, O_RDWR
    // С помощью константы O_ACCMODE нужно наложить маску
    int accessMode = flags & O_ACCMODE;
    if (accessMode == O_RDWR || accessMode == O_RDONLY) {
        printf("file is readable\n");
    }

    _exit(EXIT_SUCCESS);
}