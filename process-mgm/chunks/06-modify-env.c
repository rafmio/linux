#define _GNU_SOURCE // Для получения различных объявлений из <stdlib.h>
#include <stdlib.h>
// #include "tlpi_hdr.h"

extern char **environ;

int
main(int argc, char *argv[]) {
    int j;
    char **ep;
    clearenv();     // удаление всей среды
    
    for(j = 1; j < argc; j++) {
        if(putenv(argv[j]) != 0) {
            printf("putenv: %s\n", argv[j]);
        }
    }

    if(setenv("GREET", "Hello world", 0) == -1) {
        printf("setenv");
    }
    unsetenv("BYE");
    for (ep = environ; *ep != NULL; ep++) {
        puts(*ep);
    }

    exit(EXIT_SUCCESS);
}