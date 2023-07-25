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
    } else {
    	printf("getenv %s\n", getenv("GREET"));
    }
    
    unsetenv("BYE");
    for (ep = environ; *ep != NULL; ep++) {
        puts(*ep);
    }

    exit(EXIT_SUCCESS);
}

// int putenv(char *string);
// arg string is the form name=value
// If name does not already exist int the environment, then string added to environment
// if name is exist, then the value of name changed 

// putenv returns 0 on success
