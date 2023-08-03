#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>



int
main(int argc, char* argv[]) {


    int fd = openat(AT_FDCWD, argv[1], O_RDONLY | O_CLOEXEC);
    if (fd == -1) {
        perror("openat()");
        _exit(EXIT_FAILURE);
    }
}