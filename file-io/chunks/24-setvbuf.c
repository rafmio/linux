#include <stdio.h>
#include <string.h>
#include <unistd.h>

int
main() {
    char buff[1024];
    memset(buff, '\0', sizeof(buff)); // заполняем buff нулями

    fprintf(stdout, "Going to set full buffering on\n");
    setvbuf(stdout, buff, _IOFBF, 1024);

    fprintf(stdout, "This is rafmio host\n");
    fprintf(stdout, "This output will go into buffer\n");
    fflush(stdout);

    fprintf(stdout, "and this will appear when programn\n");
    fprintf(stdout, "will come after sleeping 5 seconds\n");

    sleep(5);


    return 0;
}

/*
_IOFBF - Full buffering
_IOLBF - Line buffering
_IONBF - No buffering
*/