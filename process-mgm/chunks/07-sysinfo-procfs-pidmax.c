#include <fcntl.h>
// #include "tlpi_hdr.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for system()
#include <string.h> // for strlen()

#define MAX_LINE 100

int
main(int argc, char *argv[]) {
    int fd;
    char line[MAX_LINE];
    ssize_t n;

    // для безопасности я не стал открывать и редактировать
    // оригинальный файл /proc/sys/kernel/pid_max, а создал копию
    fd = open("/home/raf/Volume-100-1/linux/process-mgm/chunks/pid_max", 
                        (argc > 1) ? O_RDWR : O_RDONLY);
    if (fd == -1) {
        perror("opening file");
    }

    n = read(fd, line, MAX_LINE);
    if (n == -1) {
        perror("reading file");
    }

    if (argc > 1) {
        printf("Old value: ");
    }
    printf("%.*s", (int)n, line);

    if (argc > 1) {
        if (write(fd, argv[1], strlen(argv[1])) != strlen(argv[1])) {
            perror("write() failed");
        }

        system("echo /home/raf/Volume-100-1/linux/process-mgm/chunks/pid_max now contains \
        `cat /home/raf/Volume-100-1/linux/process-mgm/chunks/pid_max`");
    }

    exit(EXIT_SUCCESS);
}