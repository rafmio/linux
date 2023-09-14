#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int
main() {
    char* args[] = {"echo", "Hello", "Tosy-Bosy", 0};
    execvp("echo", args);
    printf("execvp() failed. Error: %s\n", strerror(errno));

    return 0;
}