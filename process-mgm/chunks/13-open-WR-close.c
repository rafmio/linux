#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Too few arguments. Usage: '%s' <inputFile> <outputFile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        printf("fopen()\n");
        exit(EXIT_FAILURE);
    }

    FILE *outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        printf("fopen()");
        exit(EXIT_FAILURE);
    }

    char buffer[4096];
    while ( fgets(buffer, sizeof(buffer), inputFile) != NULL) {
        fputs(buffer, outputFile);
    }

    fflush(outputFile);

    fclose(inputFile);
    fclose(outputFile);

    exit(EXIT_SUCCESS);
}