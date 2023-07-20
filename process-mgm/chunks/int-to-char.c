#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h> // for strcat()

int main() {
    char *path = "/proc/";
    printf("path: %s\n", path);
    
    pid_t pid = 32032;
    char *pidStr = malloc(sizeof(pid_t));

    sprintf(pidStr, "%d", pid);
    printf("Process ID: %s\n", pidStr);    

    strcat(path, pidStr);
    printf("path: %s\n", path);
    return 0;
}