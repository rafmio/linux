#include <stdio.h>
#include <stdlib.h> // EXIT_FAILURE, EXIT_SUCCESS
#include <sys/types.h> // open()
#include <sys/stat.h>  // open()
#include <fcntl.h>     // open()

int
main(int argc, char const argv[]) {
    if (argc < 2) {
        printf("Too few arguments. Try againg\n");
        _exit(EXIT_FAILURE);
    }

    int sourceFd = open(argv[1], O_RDONLY);
    if (sourceFd == -1) {
        perror("open file");
        _exit(EXIT_FAILURE);
    }

        
}