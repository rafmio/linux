#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Too few arguments. Usage: '$ %s <fileName>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int ch;
    FILE* fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("opening file");
        exit(EXIT_FAILURE);
    }

    printf("Reading contents of %s:\n", argv[1]);

    while ( (ch = fgetc(fp)) != EOF ) {
        printf("%c", ch);
    }

    fclose(fp);

    exit(EXIT_SUCCESS);
}