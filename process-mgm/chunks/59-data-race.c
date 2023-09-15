#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define SH_SIZE 4

// разделяемый файловый дескриптор, с помощью которого мы ссылаемся на 
// объект в разделяемой памяти
int shared_fd = -1;

int32_t* counter = NULL;    // указатель на разделяемый счетчик

void
init_shared_resource() {
    // открываем объект в разделяемой памяти
    shared_fd = shm_open("/shm0", O_CREAT | O_RDWR, 0600);
    if (shared_fd == -1) {
        fprintf(stderr, "ERROR: Failed to create shared memory: %s\n", strerror(errno));
        exit(1);
    } else {
        fprintf(stdout, "Shared memory is created with fd: %d\n", shared_fd);
    }
}

void
shutdown_shared_resource() {
    if ( shm_unlink("/shm0") == -1 ) {
        fprintf(stderr, "ERROR: Unlinking shared memory failed: %s\n", strerror(errno));
        exit(1);
    }
}

void
inc_counter() {
    usleep(1);
    int32_t temp = *counter;
    usleep(1);
    temp++;
    usleep(1);
    *counter = temp;
    usleep(1);
}

int main() {
    // родительский процесс должен инициализировать разделяемый ресурс
    init_shared_resource();
    
    // выделяем и устанавливаем размер области памяти
    if ( ftruncate(shared_fd, SH_SIZE * sizeof(char)) == -1 ) {
        fprintf(stderr, "ERROR: Truncation failed: %s\n", strerror(errno));
        return 1;
    } else {
        fprintf(stdout, "The memory region is truncated\n");
    }

    // отражаем разделяемую память и инициализируем счетчик
    void* map = mmap(0, SH_SIZE, PROT_WRITE, MAP_SHARED, shared_fd, 0);
    if (map == MAP_FAILED) {
        fprintf(stderr, "ERROR: Mapping failed: %s\n", strerror(errno));
        return 1;
    } else {
        fprintf(stdout, "The mapping is done\n");
    }

    counter = (int32_t*)map;
    *counter = 0;

    // создаем новый процесс из текущего
    pid_t pid = fork();
    if (pid) { // родительский процесс
        inc_counter();
        fprintf(stdout, "The parent process sees the counter as %d\n", *counter);
        
        // ждем завершения дочернего процесса
        int status = -1;
        wait(&status);
        fprintf(stdout, "The child process finished with status %d\n", status);
    } else {   // дочерний процесс
        inc_counter();
        fprintf(stdout, "The child process sees the counter as: %d\n", *counter);
    }

    // оба процесса должны уничтожить отражение в области памяти и закрыть свои fd
    if ( munmap(counter, SH_SIZE) == -1 ) {
        fprintf(stderr, "ERROR: Unmapping failed: %s\n", strerror(errno));
        return 1;
    } else {
        fprintf(stdout, "Unmapping is done\n");
    }

    if ( close(shared_fd) == -1 ) {
        fprintf(stderr, "ERROR: Closing shared memory fd failed: %s\n", strerror(errno));
        return 1;
    } else {
        fprintf(stdout, "Shared memory closed\n");
    }

    // только родительскому процессу нужно закрывать разделяемый ресурс
    if (pid) {
        shutdown_shared_resource();
    }

    return 0;
}


/*
Компилировать c ключом -lrt
Скомпилировалось только без -Wall -Wextra -Werror
*/