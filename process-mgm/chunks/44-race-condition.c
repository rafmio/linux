#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

void* thread_body(void* arg) {
    char* str = (char*)arg;
    printf("inside thread_body():\nPID: %d\nTID: %d\narg: %s\n\n", getpid(), gettid(), str);

    return NULL;
}

int main() {
    pthread_t threads[6];
    int i;
    char *arguments[6] = {"Kissy", "Missy", "Tosy", "Bosy", "Huggy", "Wuggy"};
    for (i = 0; i < 6; i++) {
       int result = pthread_create(&threads[i], NULL, thread_body, arguments[i]);
       if (result) {
            printf("The threads could not be created\n");
            exit(EXIT_FAILURE);
       } 
    }

    for (i = 0; i < 6; i++) {
        int result = pthread_join(threads[i], NULL);
        if (result) {
            printf("The threads could not be joined\n");
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}