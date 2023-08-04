// fseek() и запись за пределы файла
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int
main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Too few arguments. Usage: '$ %s <InputFile> <OutputFile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *inputFp, *outputFp;

    if ( (inputFp = fopen(argv[1], "r")) == NULL ) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if ( (outputFp = fopen(argv[2], "w")) == NULL ) {
       fprintf(stderr, "Error opening file: %s\n", strerror(errno)); 
       exit(EXIT_FAILURE);
    }

    char* buffer = (char*)malloc(sizeof(char) * 4096);
    // int numRead;
    int numWrite;
    size_t len;

    while(fread(buffer, sizeof(char), sizeof(buffer), inputFp) > 0) {
        len = strlen(buffer);
        numWrite = fwrite(buffer, len, 2, outputFp);
        printf("%d bytes was worte\n", numWrite);
    }

    // int fseekRes = fseek(outputFp, 10, SEEK_END);
    // if (fseekRes != 0) {
    //     fprintf(stderr, "Error fseek: %s\n", strerror(errno));
    //     exit(EXIT_FAILURE);
    // }



    fclose(inputFp);
    exit(EXIT_SUCCESS);

}