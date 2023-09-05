#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// Стандартный заголовок POSIX для использ-я pthread
#include <pthread.h>

// Эта ф-ция (функция компаньон-потока) содержит логику, кот. должна выполняться
// как тело отдельного потока
void* thread_body(void* arg) {
    if (arg == NULL) {
        printf("arg == NULL\n");
    } 
    printf("\ninside thread_body(): \n");
    printf("Hello from first thread!\n");
    printf("PID: %d\n", getpid());
    printf("TID: %d\n", gettid()); 
    return NULL;
}

int main() {
    printf("inside main(): PID %d\n", getpid());
    printf("inside main(): TID: %d\n", gettid());

    // обработчик потоков
    pthread_t thread;  // ссылка на поток

    // создаем новый поток
    int result = pthread_create(&thread, NULL, thread_body, NULL);
    // если создание потока завершилось неудачно
    if (result) {
        printf("Thread could not be created. Error number: %d\n", result);
        exit(EXIT_FAILURE);
    } else {
        printf("result variable: %d\n", result);
    }

    // создав поток, мы его присоединяем
    // ждем, пока созданный поток не завершит работу
    result = pthread_join(thread, NULL);
    // если присоедниение потока оказалось неудачным
    if (result) {
        printf("The thread could not be joined. Error number: %d\n", result);
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

// gcc -g -Wall -Wextra -Werror -pthread 42-pthread-create.c -o 42-pthread-create.exe