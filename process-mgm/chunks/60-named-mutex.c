// https://github.com/PacktPublishing/Extreme-C/blob/master/ch18-process-synchronization/ExtremeC_examples_chapter18_2.c
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <pthread.h>

#define SHARED_MEM_SIZE 4

int          shared_fd  = -1;
int       mutex_shm_fd  = -1;
int32_t*       counter  = NULL;
pthread_mutex_t* mutex  = NULL;

void
init_control_mechanism() {
    mutex_shm_fd = shm_open("/mutex0", O_CREAT | O_RDWR, 0600);
    if (mutex_shm_fd == -1) {
        fprintf(stderr, "ERROR: Failed to create shared memory: %s\n", strerror(errno));
        exit(1);
    }

    if (ftruncate(mutex_shm_fd, sizeof(pthread_mutex_t)) == -1) {
        fprintf(stderr, "ERROR: Truncation of mutex failed: %s\n", strerror(errno));
        exit(1);
    }

    void* map = mmap(0, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED, mutex_shm_fd, 0);
    if (map == MAP_FAILED) {
        fprintf(stderr, "ERROR: Mapping failed: %s\n", strerror(errno));
        exit(1);
    }

    mutex = (pthread_mutex_t*)map;

    int ret = -1;
    pthread_mutexattr_t attr;
    if ((ret = pthread_mutexattr_init(&attr))) {
        fprintf(stderr, "ERROR: Failed to init mutex attrs: %s\n", strerror(errno));
        exit(1);
    }

    if ((ret = pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED))) {
        fprintf(stderr, "ERROR: Failed to set the mutex attr: %s\n", strerror(errno));
        exit(1);
    }

    if ((ret = pthread_mutex_init(mutex, &attr))) {
        fprintf(stderr, "ERROR: Initializing the mutex failed: %s\n", strerror(errno));
        exit(1);
    }

    if ((ret = pthread_mutexattr_destroy(&attr))) {
        fprintf(stderr, "ERROR: Failed to destroy mutex attrs: %s\n", strerror(errno));
        exit(1);
    }
}

void
shutdown_control_mechanism() {
    int ret = -1;
    if ((ret = pthread_mutex_destroy(mutex))) {
        fprintf(stderr, "ERROR: Failed to destroy mutex: %s\n", strerror(errno));
        exit(1);
    }

    if (munmap(mutex, sizeof(pthread_mutex_t)) == -1) {
        fprintf(stderr, "ERROR: Unmapping the mutex failed: %s\n", strerror(errno));
        exit(1);
    }

    if (close(mutex_shm_fd) == -1) {
        fprintf(stderr, "ERROR: Closing the mutex failed: %s\n", strerror(errno));
        exit(1);
    }

    if (shm_unlink("/mutex0") == -1) {
        fprintf(stderr, "ERROR: Unlinking the mutex failed: %s\n", strerror(errno));
        exit(1);
    }
}

void
init_shared_resourse() {
    shared_fd = shm_open("/shm0", O_CREAT | O_RDWR, 0600);
    if(shared_fd == -1) {
        fprintf(stderr, "ERROR: Failed to create shared memory: %s\n", strerror(errno));
        exit(1);
    }
    fprintf(stdout, "Shared memory is created with fd: %d\n", shared_fd);
}

void
shutdown_shared_resource() {
    if (shm_unlink("/shm0") == -1) {
        fprintf(stderr, "ERROR: Unlinking failed: %s\n");
        exit(1);
    }
}

void
inc_coutner()  {
    usleep(1);
    pthread_mutex_lock(mutex);
    int32_t temp = *counter;
    usleep(1);
    temp++;
    usleep(1);
    *counter = temp;
    pthread_mutex_unlock(mutex);
    usleep(1);
}

int
main() {
    init_shared_resourse();
    init_control_mechanism();

    if (ftruncate(shared_fd, SHARED_MEM_SIZE * sizeof(char)) == -1) {
        fprintf(stderr, "ERROR: Truncation failed: %s\n", strerror(errno));
        return 1;
    }
    fprintf(stdout, "The memory region is tructated\n");

    void* map = mmap(0, SHARED_MEM_SIZE, PROT_WRITE, MAP_SHARED, shared_fd, 0);
    if (main == MAP_FAILED) {
        fprintf(stderr, "ERROR: Mapping failed: %s\n", strerror(errno));
        return 1;
    }
    counter = (int32_t*)map;
    *counter = 0;

    pid_t pid = fork();
    if (pid) {
        inc_coutner();
        fprintf(stdout, "Parent process sees the counter as %d\n", *counter);
        int status = -1;
        wait(&status);
        fprintf(stdout, "Child process finished with status %d\n", status);
    } else {
        inc_coutner();
        fprintf(stdout, "Child processs sees the counter as %d\n", *counter);
    }

    if (munmap(counter, SHARED_MEM_SIZE) == -1) {
        fprintf(stderr, "ERROR: Unmapping failed: %s\n", strerror(errno));
        return 1;
    }

    if (close(shared_fd) == -1) {
        fprintf(stderr, "ERROR: Closing shared memory failed: %s\n", strerror(errno));
        return 1;
    }

    if (pid) {
        shutdown_shared_resource();
        shutdown_control_mechanism();
    }

    return 0;
}

/*
$ gcc -g 60-named-semaphore.c -lrt -pthread -o 60-named-semaphore.out
*/