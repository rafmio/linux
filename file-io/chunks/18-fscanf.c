#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Too few arguments. Usage: '$%s filename\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("opening file");
        exit(EXIT_FAILURE);
    }

    char buff[255];

    while ( fscanf(fp, "%s", buff) != EOF) {
        printf("%s", buff);
    }

    fclose(fp);
    exit(EXIT_SUCCESS);
}