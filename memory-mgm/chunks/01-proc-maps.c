#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char *getpathfile();

int
main(void) {

    // const int BUFFER_SIZE = 4096;
    // char buffer[BUFFER_SIZE];

    // int fd;

    char *path = getpathfile();
    printf("%s\n", path);
}

char *getpathfile() {
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

    char *result = path;

    free(pidStr);
    free(path);

    return result;
}