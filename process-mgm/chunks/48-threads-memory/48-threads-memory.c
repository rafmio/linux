#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

#define ARR_SIZE 6

void* 
thread_body(void* arg) {
    char* fileName = (char*)arg; 
    printf("Thread. PID: %d, TID: %d, arg: %s\n", getpid(), gettid(), fileName);
    char tid[8];
    char path[32];
    sprintf(tid, "%d", gettid());
    sprintf(path, "%s%s%s", "/proc/", tid, "/maps"); 

    FILE *inputFp = fopen(path, "r");
    if (inputFp == NULL) {
        perror("fopen() inputFp");
        exit(EXIT_FAILURE);
    } 
    FILE *outputFp = fopen(arg, "w");
    if (outputFp == NULL) {
        perror("fopen() outputFp");
        exit(EXIT_FAILURE);
    }

    char* buffer = (char*)malloc(4096);
    while ( fgets(buffer, sizeof(buffer), inputFp) != NULL ) {
        fputs(buffer, outputFp);
    }

    fflush(outputFp);
    fclose(inputFp);
    fclose(outputFp);
    free(buffer);

    return NULL;
}

int
main() {
    pthread_t threads[ARR_SIZE];
    int i;

    char* arguments[ARR_SIZE] = {"Kissy", "Missy", "Tosy", "Bosy", "Huggy", "Wuggy"};

    for (i = 0; i < ARR_SIZE; i++) {
        int result = pthread_create(&threads[i], NULL, thread_body, arguments[i]);
        if (result) {
            printf("Error pthread_create(): %d\n", result);
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < ARR_SIZE; i++) {
        int result = pthread_join(threads[i], NULL);
        if (result) {
            printf("Error pthread_join(): %d\n", result);
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}