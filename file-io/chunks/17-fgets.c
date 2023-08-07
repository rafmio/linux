#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Too few arguments. Usage: '%s filename\n'", argv[0]);
        exit(EXIT_FAILURE);
    }
    char str[64];
    FILE* fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("opening file");
        exit(EXIT_FAILURE);
    }

    printf("Testing fgets():\n");
    printf("Reading contents of %s:\n", argv[1]);

    while (fgets(str, 30, fp) != NULL) {
        puts(str);
    }

    fclose(fp);
    exit(EXIT_FAILURE);
}