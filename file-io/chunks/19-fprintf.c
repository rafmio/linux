// https://www.freecodecamp.org/news/file-handling-in-c-how-to-open-close-and-write-to-files/
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Too few arguments. 'Usage: %s filename filename'\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *names = fopen(argv[1], "r");
    FILE *greet = fopen(argv[2], "w");

    if (!names || !greet) {
        fprintf(stderr, "File opening failed\n");
        exit(EXIT_FAILURE);
    }

    char name[32];

    while (fscanf(names, "%s\n", name) > 0) {
        fprintf(greet, "Hello, %s!\n", name);
    }

    if (feof(names)) {
        printf("Greetings are done!\n");
    }

    exit(EXIT_SUCCESS);
}