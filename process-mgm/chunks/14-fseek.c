#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int
main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Too few arguments. Usage: '$ %s <fileName>'\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    // figure out the current position
    int fseekRes = fseek(fp, 0, SEEK_END);
    if (fseekRes != 0) {
        printf("fseek() error");
        exit(EXIT_FAILURE);
    } else {
        long file_size = ftell(fp);
        printf("Length of the file: %ld\n", file_size);
        file_size = fseek(fp, file_size / 2, SEEK_SET);
    }



    fclose(fp);

    exit(EXIT_SUCCESS);
}