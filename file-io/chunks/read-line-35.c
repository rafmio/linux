#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PROC_STATUS_FILENAME "/proc/%d/status"

int
main() {
    char filename[32];
    snprintf(filename, sizeof(filename), PROC_STATUS_FILENAME, getpid());

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("fopen()");
        exit(EXIT_FAILURE);
    } else {
        printf("file %s was opened\n", filename);
    }

    char thread_line[32];
    char buffer[32];
    int counter = 0;

    while ( fgets(buffer, sizeof(buffer), file) != NULL) {
        if (counter == 35) {
            puts(buffer);
            strncpy(thread_line, buffer, sizeof(buffer) - 10);
        }
        counter++;
    }

    exit(EXIT_SUCCESS);
}