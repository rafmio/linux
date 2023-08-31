#include <stdio.h>
#include <stdlib.h>

void print_mem_maps() {
    #ifdef __linux_
        FILE *fd = fopen("/proc/self/maps", "r");
        if (!fd) {
            perror("Could not open maps file");
            exit(EXIT_FAILURE);
        }

        char line[1024];
        while (!feof(fd)) {
            fgets(line, 1024, fd);
            printf("> %s", line);
        }
        fclose(fd);
    #endif
}

int main(int argc, char **argv) {
    // выделяем 10 байт памяти
}