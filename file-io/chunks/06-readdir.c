#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

void readFdDirFunc(char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir()");
        exit(EXIT_FAILURE);
    } 

    struct dirent *ent;

    while ( (ent = readdir(dir)) ) {
        printf("d_name: %s, d_ino: %ld, d_off: %ld, d_reclen: %d, d_type: %d\n",
            ent->d_name,
            ent->d_ino,
            ent->d_off,
            ent->d_reclen,
            ent->d_type 
        );
    }

    closedir(dir);
}

int
main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Too few arguments. Usage: '$ %s /proc/<PID>/fd'\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    readFdDirFunc(argv[1]);

    exit(EXIT_SUCCESS);
}