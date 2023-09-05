#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

// Объект мьютекса для синхронизации доступа 
// к разделяемому состоянию
pthread_mutex_t mtx;

void*
thread_body_1(void* arg) {
    // получаем указатель на разделяемую переменную
    int* shared_var_ptr = (int*)arg;

    // Критический участок
    pthread_mutex_lock(&mtx);
    (*shared_var_ptr)++;
    printf("%d\n", *shared_var_ptr);
    pthread_mutex_unlock(&mtx);

    return NULL;
}

void* 
thread_body_2(void* arg) {
    int* shared_var_ptr = (int*)arg;

    // Критический участок
    pthread_mutex_lock(&mtx);
    *shared_var_ptr += 2;
    printf("%d\n", *shared_var_ptr);
    pthread_mutex_unlock(&mtx);

    return NULL;
}

int
main() {
    // Разделяемая переменная
    int shared_var = 0;

    // Обработчики потоков
    pthread_t thread1;
    pthread_t thread2;

    // Инизиализирует мьютекс и его внутренние ресурсы
    pthread_mutex_init(&mtx, NULL);

    // Создаем новые потоки
    int result1 = pthread_create(&thread1, NULL, thread_body_1, &shared_var);
    int result2 = pthread_create(&thread2, NULL, thread_body_2, &shared_var);
    if (result1 || result2) {
        printf("Error creating thread\n");
        exit(EXIT_FAILURE);
    }

    // Ждем, пока потоки не завершат работу
    result1 = pthread_join(thread1, NULL);
    result2 = pthread_join(thread2, NULL);
    if (result1 || result2) {
        printf("Error joining\n");
        exit(EXIT_FAILURE);
    }

    pthread_mutex_destroy(&mtx);

    exit(EXIT_SUCCESS);
}