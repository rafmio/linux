#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
main(int argc, char *argv[]) {
    char *argVec[10];
    char *envVec[] = { "GREET=salut", "BYE=adieu", NULL };

    if (argc != 2 || strcmp(argv[1], "--help") == 0) {
        printf("Wrong usage. Usage: %s pathname\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    argVec[0] = strrchr(argv[1], '/');
    printf("\n\nstrrchr(argv[1]: '/') %s\n\n", argVec[0]);
    // Получаем последнюю часть имени файла из argv[1]
    if (argVec[0] != NULL)
        argVec[0]++;
    else
        argVec[0] = argv[1];

    argVec[1] = "hello world";
    argVec[2] = "goodbye";
    argVec[3] = NULL; // В конце списка должно быть значение NULL

    execve(argv[1], argVec, envVec);

    exit(EXIT_SUCCESS);
}

/*

$ ./36-execve ./37-envargs.c

*/