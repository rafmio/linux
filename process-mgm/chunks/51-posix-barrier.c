#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

// объект барьера
pthread_barrier_t barrier;

void*
thread_body_1(void* arg) {
    int* thread_num = (int*)arg;
    printf("Thread num: %d, A - PID: %d, TID: %d\n", *(thread_num + 0), getpid(), gettid());
    pthread_barrier_wait(&barrier);

    return NULL;
}

void*
thread_body_2(void* arg) {
    int* thread_num = (int*)arg; 
    // ждем присоединения другого потока
    pthread_barrier_wait(&barrier);
    printf("Thread num: %d, B - PID: %d, TID: %d\n", *(thread_num + 1), getpid(), gettid());
    return NULL;
}

int
main() {
    // инициализируем объект барьера
    pthread_barrier_init(&barrier, NULL, 2);
    int thread_num[2] = {1, 2};
    // обработчики потоков
    pthread_t thread1;
    pthread_t thread2;

    // создаем новые потоки
    int result1 = pthread_create(&thread1, NULL, thread_body_1, thread_num);
    int result2 = pthread_create(&thread2, NULL, thread_body_2, thread_num);
    if (result1 || result2) {
        printf("pthread_create()\n");
        exit(EXIT_FAILURE);
    }

    // ждем пока потоки не завершат работу 
    result1 = pthread_join(thread1, NULL);
    result2 = pthread_join(thread2, NULL);
    if (result1 || result2) {
        printf("pthread_join()\n");
        exit(EXIT_FAILURE);
    }

    // уничтожаем объект барьера
    pthread_barrier_destroy(&barrier);

    return 0;
}