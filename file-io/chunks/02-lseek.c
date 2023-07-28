#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>


#define BUF_SIZE 64

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("too few argunets\nusage: %s fileName\ntry again\n", argv[1]);
        _exit(EXIT_FAILURE);
    }

    int nRead, nWrite, fd;
    char buff[BUF_SIZE];
    off_t offset;

    fd = open(argv[1], O_RDWR | O_CLOEXEC);
    if (fd < 0) {
        perror("opening file");
        _exit(EXIT_FAILURE);
    } else {
        printf("fd: %d\n", fd);
        printf("pid: %d\n", getpid());
    }

    nRead = read(fd, buff, BUF_SIZE);
    if (nRead < 0) {
        perror("reading file");
        _exit(EXIT_FAILURE);
    } else {
        printf("read bytes: %d\n", nRead);
    }

    nWrite = write(STDOUT_FILENO, buff, BUF_SIZE);
    if (nWrite < 0) {
        perror("write to STDOUT_FILENO");
        _exit(EXIT_FAILURE);
    } else {
        printf("\nwrote %d bytes\n", nWrite);
    }

    offset = lseek(fd, 5, SEEK_CUR);
    if (offset < 0) {
        perror("lseek");
        _exit(EXIT_FAILURE);
    } else {
        printf("offset was set at %ld bytes\n", offset);
    }

    nRead = read(fd, buff, BUF_SIZE);
    if (nRead < 0) {
        perror("reading file");
        _exit(EXIT_FAILURE);
    } else {
        printf("read bytes: %d\n", nRead);
    }

    nWrite = write(STDOUT_FILENO, buff, BUF_SIZE);
    if (nWrite < 0) {
        perror("write to STDOUT_FILENO");
        _exit(EXIT_FAILURE);
    } else {
        printf("\nwrote %d bytes\n", nWrite);
    }
}