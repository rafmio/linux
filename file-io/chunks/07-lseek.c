#include <stdio.h>
#include <stdlib.h> // EXIT_FAILURE, EXIT_SUCCESS
#include <sys/types.h> // open()
#include <sys/stat.h>  // open()
#include <fcntl.h>     // open()
#include <unistd.h>    // _exit()

#define BUFFER_SIZE 4096

int
main(int argc, char const *argv[]) {
    int readNum;
    // int writeNum;
    char buffer[4096];


    if (argc < 3) {
        printf("Too few arguments. Usage: '$ %s sourceFile distinationFile'. Try againg\n", argv[0]);
        _exit(EXIT_FAILURE);
    }

// SOURCE FILE: ---------------------------------------------------
    int sourceFd = open(argv[1], O_RDONLY);
    if (sourceFd == -1) {
        perror("open file");
        _exit(EXIT_FAILURE);
    } else {
        int position = lseek(sourceFd, 0, SEEK_CUR);
        if (position == -1) {
            perror("lseek()");
            _exit(EXIT_FAILURE);
        } else {
            printf("Current source file position: %d\n", position);
        }
    }

// DISTINATION FILE: ----------------------------------------------
    int openFlags = O_CREAT | O_RDWR;
    int filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
    int distFd = open(argv[2], openFlags, filePerms); 
    if (distFd == -1) {
        perror("open distFd");
        _exit(EXIT_FAILURE);
    } else {
        int position = lseek(sourceFd, 0, SEEK_CUR);
        printf("Current distination file position: %d\n", position);
        printf("Let's check the length of the distFd: %ld\n", lseek(distFd, 0, SEEK_END));
    }

// SHIFT FILE POSITION: --------------------------------------------
    printf("\n");
    printf("Let's check the length of the file:\n"); 
    int lenSrcFd = lseek(sourceFd, 0, SEEK_END);
    printf("lenSrcFd: %d\n", lenSrcFd);


    printf("Let's shift this position at centre:\n");
    int position = lseek(sourceFd, -1 * (lenSrcFd / 2), SEEK_END);
    printf("file position at source file now is: %d\n", position);

// WRITE FROM CENTER TO END: ---------------------------------------
    while( (readNum = read(sourceFd, buffer, BUFFER_SIZE)) > 0) {
        if (write(distFd, buffer, BUFFER_SIZE) != readNum) {
            printf("can't write whole buffer\n");
        }
        printf("%d bytes was wrote\n", readNum);
    }

// READ DISTINATION FILE: ------------------------------------------



    close(sourceFd);
    close(distFd);

    _exit(EXIT_SUCCESS);
}