#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#define TRUE 1
#define FALSE 0

typedef unsigned int bool_t;

// Структура для хранения всех переменных, относящихся
// к разделяемому состоянию
typedef struct {
    bool_t done;         // флаг, показывающ. был выведен символ А или нет
    pthread_mutex_t mtx; // объект мьютекса для защиты критического участка
    pthread_cond_t cv;   // условная переменная для синх-ции двух потоков
} shared_state_t;

// Инициализирует члены объекта shared_state_t
void shared_state_init(shared_state_t *shared_state) {
    shared_state->done = FALSE;
    pthread_mutex_init(&shared_state->mtx, NULL);
    // shated_state->mtx = PTHREAD_MUTEX_INITIALIZER - альтернатива pthread_mutex_init()
    pthread_cond_init(&shared_state->cv, NULL);
}

// Уничтожает члены объекта shared_state_t
void shared_state_destroy(shared_state_t *shared_state) {
    pthread_mutex_destroy(&shared_state->mtx);
    pthread_cond_destroy(&shared_state->cv);
}

void* thread_body_1(void* arg) {
    shared_state_t* ss = (shared_state_t*)arg; 
    pthread_mutex_lock(&ss->mtx);
    printf("A\n");
    ss->done = TRUE;

    pthread_cond_signal(&ss->cv);  // Шлем сигинал потокам, ожадиющ. усл-й переменной
    pthread_mutex_unlock(&ss->mtx);

    return NULL;
}

void* thread_body_2(void* arg) {
    shared_state_t *ss = (shared_state_t*)arg;
    pthread_mutex_lock(&ss->mtx);

    // Ждем, пока флан не станет равным TRUE
    while (!ss-> done) {
        pthread_cond_wait(&ss->cv, &ss->mtx); // ждем усл-ю переменную
    }
    printf("B\n");
    pthread_mutex_unlock(&ss->mtx);

    return NULL;
}

int main() {
    shared_state_t shared_state;      // Разделяемое состояние
    shared_state_init(&shared_state); // Инизиализируем разделяемое состояние

    pthread_t thread1;                // Обработчик потоков
    pthread_t thread2;                // Обработчик потоков

    // Создаем новые потоки    
    int result1 = pthread_create(&thread1, NULL, thread_body_1, &shared_state);
    int result2 = pthread_create(&thread2, NULL, thread_body_2, &shared_state);
    if (result1 || result2) {
        printf("Error createing threads\n");
        exit(EXIT_FAILURE);
    }

    result1 = pthread_join(thread1, NULL); // Ждем, пока потокм не завершат работу
    result2 = pthread_join(thread2, NULL); // Ждем, пока потоки не завершат рабботу
    if (result1 || result2) {
        printf("The threads could not be joined\n");
        exit(EXIT_FAILURE);
    }

    // Уничтожаем разделяемое состояние, освобождаем мьютекс 
    // и объекты условных переменных
    shared_state_destroy(&shared_state);

    exit(EXIT_SUCCESS);
}