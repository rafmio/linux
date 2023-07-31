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

/*
#define _GNU_SOURCE в C-программах для включения поддержки GNU-специфических функций и макросов. Она позволяет использовать функции, которые не поддерживаются стандартной библиотекой языка Си, такие как функции для работы с файлами и процессами.

Например, если вы пишете программу, которая должна работать на разных платформах, то использование этой строки может помочь вам избежать ошибок при компиляции программы на системах, где эти функции не поддерживаются.

Также эта строка может использоваться для включения дополнительных возможностей, которые предоставляет GNU C Library (Glibc), таких как поддержка многопоточности и работа с сетью.

В целом, использование этой строки является хорошей практикой для написания переносимых и надежных программ на языке Си.
*/
