#include <stdio.h>
#include <string.h>
#include <unistd.h>

void constructPath(char* path);

int main() {
    char path[128];
    constructPath(path);

    printf("path: '%s'\n", path);

    return 0;
}

void constructPath(char* path) {
    char procDir[] = "/proc/";
    char fdDir[] = "/fd";
    char pid[8];
    sprintf(pid, "%d", getpid());

    strcat(path, procDir);
    strcat(path, pid);
    strcat(path, fdDir);
}

