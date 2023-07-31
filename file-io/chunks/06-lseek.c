#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h> // for readdir()
#include <string.h> // for strcat()

void getProcPidFdDir(char* pathProcPidFd) {
    char procDir[] = "/proc/";
    char fdDir[] = "/fd";
    char pid[8];
    sprintf(pid, "%d", getpid());

    strcat(pathProcPidFd, procDir);
    strcat(pathProcPidFd, pid);
    strcat(pathProcPidFd, fdDir);
}

void fileStatInfo(int inputFd) {
    struct stat statFd;
    int statRes = fstat(inputFd, &statFd);
    if (statRes == -1) {
        perror("fstat()");
        _exit(EXIT_FAILURE);
    } else {
        printf("fstat() for fd %d:\n", inputFd);
        printf("st_dev\t\t%ld\t - ID of device containing file\n", statFd.st_dev);
        printf("st_ino\t\t%ld\t - Inode number\n", statFd.st_ino);
        printf("st_mode\t\t%d\t - File type and mode\n", statFd.st_mode);
        printf("st_nlink\t%ld\t - Number of hard links\n", statFd.st_nlink);
        printf("st_uid\t\t%d\t - UID of owner\n", statFd.st_uid);
        printf("st_gid\t\t%d\t - GID of owner\n", statFd.st_gid);
        printf("st_rdev\t\t%ld\t - Device ID (if special file)\n", statFd.st_rdev);
        printf("st_size\t\t%ld\t - Total size, in bytes\n", statFd.st_size);
        printf("st_blksize\t%ld\t - Block size for filesystems I/O\n", statFd.st_blksize);
        printf("st_blocks\t%ld\t - Number of 512B blocks allocated\n", statFd.st_blocks);

        printf("st_atim:\t%ld - Time of last access\n", statFd.st_atime);
        printf("st_mtime:\t%ld - Time of last modification\n", statFd.st_mtime);
        printf("st_ctime:\t%ld - Time of last status change\n", statFd.st_ctime);
    }
}

void lsProcPidFdDir(char* pathProcPidFd) {
    char *cmd = (char*)malloc(sizeof("ls -l ") + sizeof(pathProcPidFd));
    sprintf(cmd, "%s%s", "ls -la ", pathProcPidFd);

    printf("lsProcPidFdDir() for %s:\n", pathProcPidFd);
    system(cmd);

    free(cmd);

    printf("\n");
}

off_t calcSize(int fd) {
    struct stat stFd;
    int statRes = fstat(fd, &stFd);
    if (statRes == -1) {
        perror("fstat()");
        _exit(EXIT_FAILURE);
    } else {
        return stFd.st_size;
    }
}

void readFdDirFunc(char *path) {
    DIR *dir = opendir(path);
    struct dirent *ent;

    if (dir == NULL) {
        perror("opendir()");
        _exit(EXIT_FAILURE);
    }

    while( (ent = readdir(dir)) ) {
        printf("d_ino: %ld, d_off: %ld, d_reclen: %d, d_type: %d, d_name: %s\n", 
            ent->d_ino,     // inode number
            ent->d_off,     // position in the directory stream
            ent->d_reclen,  // length of this record
            ent->d_type,    // type of file 
            ent->d_name     // filename
        );
    }

    closedir(dir);
}


int
main(int argc, char const *argv[]) {
    int inputFd;                                   
    int readNum;
    char pathProcPidFd[128]; // varable for containing path /proc/<PID>/fd


    // chech for amount of command line arguments
    if (argc < 2) {
        printf("Too few arguments. Usage: $ %s filename\n", argv[0]);
        _exit(EXIT_FAILURE);
    } else {  
        // if ok - open second command line argument filename
        inputFd = open(argv[1], O_RDONLY);   // without O_CLOEXEC
        if (inputFd == -1) {
            perror("opening file");
            _exit(EXIT_FAILURE);
        }
    }

    getProcPidFdDir(pathProcPidFd);      // get char path for /proc/<PID>/fd
    fileStatInfo(inputFd);               // info about opened file 
    printf("\n");
    lsProcPidFdDir(pathProcPidFd);       // $ ls -la /proc/<PID>/fd

    // get size of file
    off_t fileSize = calcSize(inputFd);
    printf("calSize(fd): %ld\n", fileSize);
    int position = (int) fileSize / 4 * 3;
    printf("position / 4 * 3: %d\n", position);
    printf("\n");

    // change fileposition
    if (lseek(inputFd, position, SEEK_SET) == -1) {
        perror("lseek()");
        _exit(EXIT_FAILURE);
    } else {
        char buf[fileSize / 4];
        while( (readNum = read(inputFd, buf, fileSize / 4)) > 0) {
            if (write(STDOUT_FILENO, buf, readNum) != readNum) {
                printf("couldn't write whole buffer\n");
            }
        }

        int currPosAfterRead = lseek(inputFd, 0, SEEK_CUR);
        if (currPosAfterRead == -1) {
            perror("lseek()");
            _exit(EXIT_FAILURE);
        } else {
            printf("Current file position: %d\n", currPosAfterRead);
        }
    }

    if ( close(inputFd) == -1 ) {
        perror("closing file");
        _exit(EXIT_FAILURE);
    }

    readFdDirFunc(pathProcPidFd);

    _exit(EXIT_SUCCESS);
}
