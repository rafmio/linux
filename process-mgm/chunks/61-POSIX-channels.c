#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int
main() {
    int fds[2];
    pipe(fds);
    fprintf(stdout, "fds[0]: %d,fds[1]: %d\n\n", fds[0], fds[1]);

    int childPid = fork();
    if (childPid == -1) {
        fprintf(stderr, "fork error!\n");
        exit(1);
    }

    if (childPid == 0) {
        // потомок закрывает fd для чтения
        close(fds[0]);
        char str[] = "Hello Daddy!";

        // потомок записывает в fd, открытый для записи
        fprintf(stdout, "CHILD: Waiting for 2 seconds...\n");
        sleep(2);
        fprintf(stdout, "CHILD: Writing to daddy... \n");
        write(fds[1], str, strlen(str) + 1);
    } else {
        // родитель закрывает fd для записи
        close(fds[1]);
        char buff[32];

        // родитель читает из fd, открытого для чтения
        fprintf(stdout, "PARENT: Reading from child...\n");
        int num_of_reads = read(fds[0], buff, 32);
        fprintf(stdout, "Read from fds[0]: %d\n", num_of_reads);
        fprintf(stdout, "PARENT: Received from child: %s\n", buff);
    }

    return 0;
}