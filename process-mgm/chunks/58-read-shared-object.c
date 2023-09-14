#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define SH_SIZE 16

int
main() {
    int shm_fd = shm_open("/shm0", O_RDONLY, 0600);
    if (shm_fd == -1) {
        fprintf(stderr, "ERROR: Failed to open shared memory: %s\n", strerror(errno));
        return 1;
    } else {
        fprintf(stdout, "Shared memory is opened with fd: %d\n", shm_fd);
    }

    void* map = mmap(0, SH_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (map == MAP_FAILED) {
        fprintf(stderr, "ERROR: Mapping failed: %s\n", strerror(errno));
        return 1;
    }

    char* ptr = (char*)map;
    fprintf(stdout, "The contents of shared memory object: %s\n", ptr);

    // unmapping
    if ( munmap(ptr, SH_SIZE) == -1 ) {
        fprintf(stderr, "ERROR: Unmapping failed: %s\n", strerror(errno));
        return 1;
    }

    // removing preivously created object
    if ( shm_unlink("/shm0") == -1 ) {
        fprintf(stderr, "ERROR: Unlinking shared memory failed: %s\n", strerror(errno));
        return 1;
    }

    return 0;
}

/*
Компилировать c ключом -lrt
Скомпилировалось только без -Wall -Wextra -Werror

$ ls /dev/shm
*/