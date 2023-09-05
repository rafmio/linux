// Программа - пример гонки данных
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

void*
thread_body_1(void* arg) {
    // Получаем указатель на разделяемую переменную
    int* shared_var_ptr = (int*)arg;

    // Инкрементируем разделяемую переменную на 1, выполняя запись
    // непосредственно по ее адресу в памяти
    (*shared_var_ptr)++;
    printf("%d\n", *shared_var_ptr);
    return NULL;
}

void*
thread_body_2(void* arg) {
    // Получаем указатель на разделяемую переменную
    int* shared_var_ptr = (int*)arg;

    // Инкрементируем разделяемую переменную на 2, выполняя запись
    // непосредственно по ее адреу в памяти
    *shared_var_ptr += 2;
    printf("%d\n", *shared_var_ptr);
    return NULL;
}

int
main() {
    // Разделяемая переменная, расположена в стеке главного потока
    int shared_var = 0;

    // Обработчики потоков
    pthread_t thread1;
    pthread_t thread2;

    // Создаём новые потоки
    int result1 = pthread_create(&thread1, NULL, thread_body_1, &shared_var);
    int result2 = pthread_create(&thread2, NULL, thread_body_2, &shared_var);
    if (result1 || result2) {
        printf("The threads could not be created\n");
        exit(EXIT_FAILURE);
    }

    // Ждём, пока потоки не завершат работу
    result1 = pthread_join(thread1, NULL);
    result2 = pthread_join(thread2, NULL);
    if (result1 || result2) {
        printf("The threads could not be joined\n");
    }

    exit(EXIT_SUCCESS);
}

// В этих потоках указатель никогда не станет висячим, т.к. главный поток их 
// присоединяет и не завершается, пока они не отработают

