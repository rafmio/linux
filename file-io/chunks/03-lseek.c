#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h> // for readdir()

void lsProcPidFdDir();
void printFdStat(int fd);
off_t calcSize(int fd); // we can find size using lseek(fd, 0, SEEK_END);

int
main(int argc, char *argv[]) {
    int inputFd; 
    // int outputFd;
    int readNum;
    // int writeNum;
    // check for command args
    if (argc < 2) {
        printf("Too few aguments. Usage: $ %s fileName\n", argv[1]);
        _exit(EXIT_FAILURE);
    } else { // if ok - open argv[1]
        inputFd = open(argv[1], O_RDONLY);
        if (inputFd == -1) {
            perror("opening input file");
            _exit(EXIT_FAILURE);
        }
    }

    lsProcPidFdDir();           // list open files for PID
    printFdStat(inputFd);      // check stat of inputFd file

    // change file position close to EOF:
    printf("\n");
    off_t fileSize = calcSize(inputFd);
    printf("calcSize(fd): %ld\n", fileSize);
    int newPosition = (int) fileSize / 4 * 3;
    printf("newPosition fileSize / 4 * 3: %d\n", newPosition);
    printf("\n");

    if (lseek(inputFd, newPosition, SEEK_SET) == -1) {
        perror("lseek()");
        _exit(EXIT_FAILURE);
    } else {
        char buf[fileSize / 4];
        while( (readNum = read(inputFd, buf, fileSize / 4)) > 0) {
            if (write(STDOUT_FILENO, buf, readNum) != readNum) {
                printf("couldn't write whole buffer");
            }
        }
        // check for current file position
        int currPosAfterWread = lseek(inputFd, 0, SEEK_CUR);
        if (currPosAfterWread == -1) {
            perror("lseek()");
            _exit(EXIT_FAILURE);
        } else {
            printf("Current file position: %d\n", currPosAfterWread);
        }
    }

    if ( close(inputFd) == -1 ) {
        printf("closing inputFd");
        _exit(EXIT_FAILURE);
    }

    // lsProcPidFdDir(); // - вместо system(lsDir) используем readdir(3)


    _exit(EXIT_SUCCESS);
}

void lsProcPidFdDir() {
    char *procDir = "/proc/";
    char *fdDir = "/fd";
    char *pidStr = (char*) malloc(sizeof(int));  
    char *cmd = (char*) malloc(sizeof("ls -l ") + sizeof(procDir) + sizeof(int) + sizeof(fdDir));
    sprintf(pidStr, "%d", getpid());
    sprintf(cmd, "%s%s%s%s", "ls -l ", procDir, pidStr, fdDir);
    printf("\nFor PID %s:\n", pidStr); 
    system(cmd);

    free(pidStr);
    free(cmd);
}

void printFdStat(int fd) {
    struct stat statFd;
    int statRes = fstat(fd, &statFd);
    if (statRes == -1) {
        perror("fstat()");
        _exit(EXIT_FAILURE);
    } else {
        printf("\nfstat() for fd %d:\n", fd);
        printf("st_dev\t\t%ld\t-ID of device containing file\n", statFd.st_dev);
        printf("st_ino\t\t%ld\t - Inodenumber\n", statFd.st_ino);
        printf("st_mode\t\t%d\t - File type and mode\n", statFd.st_mode);
        printf("st_nlink\t%ld\t - Number of hard links\n", statFd.st_nlink);
        printf("st_uid\t\t%d\t - UID of owner\n", statFd.st_uid);
        printf("st_gid\t\t%d\t - GID of owner\n", statFd.st_gid);
        printf("st_rdev\t\t%ld\t - Device ID (if special file)\n", statFd.st_rdev);
        printf("st_size\t\t%ld\t - Total size, in bytes\n", statFd.st_size);
        printf("st_blksize\t%ld\t - Block size for filesystems I/O\n", statFd.st_blksize);
        printf("st_blocks\t%ld\t - Number of 512B blocks allocated\n", statFd.st_blocks);

        printf("st_atim:\t%ld - Time of last access\n", statFd.st_atime);
        printf("st_mtime\t%ld - Time of last modification\n", statFd.st_mtime);
        printf("st_ctime\t%ld - Time of last status change\n", statFd.st_ctime);
    }
}

off_t calcSize(int fd) {
    struct stat stFd;
    int statRes = fstat(fd, &stFd);
    if (statRes == -1) {
        perror("fstat()");
        _exit(EXIT_FAILURE);
    } else {
        return (off_t) stFd.st_size;
    }
}

