#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void getpathfile(char *path);

int
main(void) {
    char *directory = "/proc/";
    char *file = "/maps";

    // выделяем место для переменной, которая будет хранить pid в строке
    char *pidStr = malloc(sizeof(pid_t));

    // внутри функции sprintf() запрашиваем текущий pid и конвертируем его в 
    // с троку и кладём в переменную pidStr
    sprintf(pidStr, "%d", getpid());

    // выделяем место для переменной, которая будет хранить полный путь
    char *path = malloc(sizeof(directory) + sizeof(pidStr) + sizeof(file));
    // конструируем путь:
    sprintf(path, "%s%s%s", directory, pidStr, file);

    // free(pidStr);
    // free(path);

    const int BUFFER_SIZE = 4096;
    char buffer[BUFFER_SIZE];
    int fd;
    fd = openat(AT_FDCWD, path, O_RDONLY);
    if (fd < 0) {
        perror("error opening file\n");
        return 1;
    }

    ssize_t contents = read(fd, buffer, BUFFER_SIZE);
    if (contents < 0) {
        perror("error reading file\n");
        return 1;
    } else {
        close(fd);
        free(pidStr);
        free(path);
    }

    int stdout = 1;
    write(stdout, buffer, contents);
    printf("\n");

    return 0;
}