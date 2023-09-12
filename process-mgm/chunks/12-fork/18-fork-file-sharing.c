// temp file, temporary file, временный файл
// file sharing
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int
main() {
    
    int fd, flags;
    char template[] = "/tmp/textXXXXXX";

    setbuf(stdout, NULL);   // Отключаем буферизацию стандартного вывода

    fd = mkstemp(template);
    if (fd == -1) {
        perror("mkstemp()");
    }

    printf("File offset before fork(): %lld\n", (long long) lseek(fd, 0, SEEK_CUR));
    flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        perror("fcntl()");
    } else {
        printf("fcntl(fd, F_GETFL): %d\n", flags);
    }
    printf("O_APPEND flag before fork() is: [%s]\n", (flags & O_APPEND) ? "on" : "off");

    switch (fork()) {
        case -1:
            perror("fork()");
            exit(EXIT_FAILURE);
        case 0:                 // Потомок изменяет сдвиг файла и флаги его состояния
            if (lseek(fd, 1000, SEEK_SET) == -1) {
                perror("lseek()");
                exit(EXIT_FAILURE);
            }

            flags = fcntl(fd, F_GETFL);     // Извлекаем текущие флаги
            if (flags == -1) {
                perror("fcntl()");
                exit(EXIT_FAILURE);
            } else {
                printf("fcntl(fd, F_GETFL): %d\n", flags);
            }

            flags |= O_APPEND;              // Устанавливаем флаг O_APPEND
            if (fcntl(fd, F_SETFL, flags) == -1) {
                perror("fcntl() F_SETFL");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_FAILURE);

        default:    // Родитель может видеть изменения, внесенные потомком
            if (wait(NULL) == -1) {
                perror("wait()");
                exit(EXIT_FAILURE);
            }
            printf("Child has exited\n");

            printf("File offset in parent: %lld\n", (long long) lseek(fd, 0, SEEK_CUR));

            flags = fcntl(fd, F_GETFL);
            if (flags == -1) {
                perror("fcntl() F_GETFL");
                exit(EXIT_FAILURE);
            }

            printf("O_APPEND flag in parent is: %s\n", (flags & O_APPEND) ? "on" : "off");
            exit(EXIT_SUCCESS);

    }
}