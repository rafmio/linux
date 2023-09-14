#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#include <semaphore.h>

// Главный указатель на объект семафора, применяемый для 
// синхронизации доступа к разделяемому состоянию
sem_t* semaphore;

void*
thread_body_1(void* arg) {
    // получаем указатель на разделяемую переменную
    int* shared_var_ptr = (int*)arg;
    // ждем семафор
    sem_wait(semaphore);

    // инкрементируем разделяемую переменную на 1, выполняя запись
    // непосредственно по ее адресу в памяти
    (*shared_var_ptr)++;
    printf("*shared_var_ptr: %d\n", *shared_var_ptr);

    // освобождаем семафор
    sem_post(semaphore);

    return NULL;
}

void*
thread_body_2(void* arg) {
    // получаем указатель на разделяемую переменную
    int* shared_var_ptr = (int*)arg;
    
    // ждем семафор
    sem_wait(semaphore);

    // инкрементируем разделяемую переменную на 2, выполняя запись
    // непосредственно по ее адресу в памяти
    (*shared_var_ptr) += 2;
    printf("%d\n", *shared_var_ptr);

    // освобождаем семафор
    sem_post(semaphore);
    
    return NULL;
}

int
main() {
    int shared_var = 0;

    #ifdef __APPLE__
    // неименованные семафоры не поддерживаются в OS/X. Поэтому семафор нужно 
    // инициализировать как именованный, используя sem_open()
        semaphore = sem_open("sem0", O_CREAT | O_EXCL, 0655, 1);
    #else
        sem_t local_semaphore;
        semaphore = &local_semaphore;
        
        // инициализируем семафор как мьютекс (двоичный семафор)
        sem_init(semaphore, 0, 1);
    #endif


    pthread_t thread1;
    pthread_t thread2;

    int result1 = pthread_create(&thread1, NULL, thread_body_1, &shared_var);
    int result2 = pthread_create(&thread2, NULL, thread_body_2, &shared_var);
    if (result1 || result2) {
        printf("pthread_create()");
        exit(EXIT_FAILURE);
    } else {
        printf("threads was created\n");
    }

    result1 = pthread_join(thread1, NULL);
    result2 = pthread_join(thread2, NULL);
    if (result1 || result2) {
        printf("pthread_join()");
        exit(EXIT_FAILURE);
    } else {
        printf("threads was joined\n");
    }

    exit(EXIT_SUCCESS);
}