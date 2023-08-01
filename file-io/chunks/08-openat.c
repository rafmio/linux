#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int
main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Too few arguments. Useage: '$ %s filenage'\n", argv[0]);
        _exit(EXIT_FAILURE);
    }
    int fd = openat(AT_FDCWD, argv[1], O_RDONLY);
    if (fd == -1) {
        perror("opening file");
        _exit(EXIT_FAILURE);
    }

    printf("FD: %d\n", fd);

    close(fd);

    _exit(EXIT_SUCCESS);

}