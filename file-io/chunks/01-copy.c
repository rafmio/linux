/* - open file only for read
*  - file for opening specified in command line arguments
*  - read data from file
*  - create new file if it is not exits
*  - write data to the new file
*/
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef BUF_SIZE        // Позволяет "cc -D" перекрыть определение
#define BUF_SIZE 1024
#endif

int
main(int argc, char *argv[]) {
    int inputFd, outputFd, openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE];

    // При запуске программы нужно ввести аргументы, проверяем их
    if(argc != 3 || strcmp(argv[1], "--help") == 0) {// если аргументов не 3 или второй - не хелп...
        printf("%s old-file new-file\n", argv[0]); 
    }

    // Открытие файлов ввода и вывода
    inputFd = open(argv[1], O_RDONLY);
    if(inputFd == -1) {
        perror("opening file");
        exit(EXIT_FAILURE);
    }

    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR  | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; // rw-rw-rw-

    outputFd = open(argv[2], openFlags, filePerms);
    if(outputFd == -1) {
        perror("opening file");
        exit(EXIT_FAILURE);
    }

    // Перемещение данных до достиж-я конца файла ввода или возник-я ошибки:
    while( (numRead = read(inputFd, buf, BUF_SIZE)) > 0) {
        if(write(outputFd, buf, numRead) != numRead) {
            printf("could't write whole buffer");
        }
    }
    // при наступлении каких условий происходит выход из while? 
    
    if( numRead == -1 ) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    if( close(inputFd) == -1 ) {
        perror("close input");
        exit(EXIT_FAILURE);
    }
    if( close(outputFd) == -1 ) {
        perror("close output");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

// ./01-copy.exe /proc/self/maps maps.txt - копирование обычного файла
// ./01-copy.exe maps.txt /dev/tty - копировать обычный файл в это терминал

// read() returns zero if:
// - the file offset is at or past the end of file
// - no bytes are read
