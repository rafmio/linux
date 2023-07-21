#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h> // for strcat()

int main() {
    char *path = "/proc/";
    char *file = "/maps";

    // converting pid_t to string (char): 
    pid_t pid = 32032;
    char *pidStr = malloc(sizeof(pid_t));
    sprintf(pidStr, "%d", pid);

    // Конструируем строку с путём к файлу
    char *fullPath = malloc(strlen(path) + strlen(pidStr) + strlen(file));
    sprintf(fullPath, "%s%s%s", path, pidStr, file);

    printf("%s\n", fullPath);

    free(pidStr);
    free(fullPath);


    return 0;
}