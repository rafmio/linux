#define _GNU_SOURCE
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

void* thread_body(void* arg) {
    printf("inside thread_body()\n");
    printf("PID: %d\n", getpid());
    printf("TID: %d\n", gettid());
    return arg;
}

int 
main() {
    printf("\ninside main():\n");
    printf("PID: %d\n", getpid());
    printf("TID: %d\n\n", gettid());

    pthread_t thread;   

    // Create new thread
    int result = pthread_create(&thread, NULL, thread_body, NULL);
    if (result) {
        printf("Thread could not be created. Error: %d\n", result);
        exit(EXIT_FAILURE);
    }

    // Отсоединяем поток
    result = pthread_detach(thread);
    if (result) {
        printf("Thread could not be detached. Error: %d\n", result);
        exit(EXIT_FAILURE);
    }

    // Выходим из главного потока
    pthread_exit(NULL);  // чтобы процесс дождался завершения отсоединенного потока

    exit(EXIT_SUCCESS);
}