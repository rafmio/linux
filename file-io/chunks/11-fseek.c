#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int
main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Too few arguments. Usage: '$ %s <fileName>'\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    // figure out the current position
    int fseekRes = fseek(fp, 0, SEEK_END);
    if (fseekRes != 0) {
        printf("fseek() error");
        exit(EXIT_FAILURE);
    } else {
        long file_size = ftello(fp);    // return current file position
        printf("Length of the file: %ld\n", file_size);
        fseek(fp, file_size / 2, SEEK_SET);

        char buffer[file_size / 2];

        FILE *outputFile = fopen(argv[2], "w");
        if (outputFile == NULL) {
            printf("error fopen()\n");
            exit(EXIT_FAILURE);
        }

        while ( fgets(buffer, sizeof(buffer), fp) != NULL ) {
            fputs(buffer, outputFile);
        }

        fflush(outputFile);
        fclose(outputFile);
    }

    fclose(fp);

    exit(EXIT_SUCCESS);
}