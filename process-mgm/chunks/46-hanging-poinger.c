// Висячие указатели. Это приводит к нарушению работы памяти
// Однако в данном примере неполадки скорее всего не проявятся
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>

void* thread_body(void *arg) {
    char *str = (char*)arg;
    printf("PID: %d, TID: %d, %s\n", getpid(), gettid(), str);

    return NULL;
}

int
main() {
    // обработчики потоков
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;

    // массивы символов, выделенные в стеке главного потока
    char str1[8], str2[8], str3[8];
    stpcpy(str1, "Apple");
    strcpy(str2, "Orange");
    strcpy(str3, "Lemon");

    // если я правильно понял, то тут дочерним потокам передается указатель
    // на переменную в стеке главного потока 
    int result1 = pthread_create(&thread1, NULL, thread_body, str1);
    int result2 = pthread_create(&thread2, NULL, thread_body, str2);
    int result3 = pthread_create(&thread3, NULL, thread_body, str3);

    if (result1 || result2 || result3) {
        printf("The threads couldn't be created\n");
        exit(EXIT_FAILURE);
    }

    // отсоединяем потоки. В результате отсоединения объявленные на вершине стека
    // главного потока переменные будут удалены, и в некот. чередованиях потоки
    // могут обратиться к уже висячим указателям 
    result1 = pthread_detach(thread1);
    result2 = pthread_detach(thread2);
    result3 = pthread_detach(thread3);
    if (result1 || result2 || result3) {
        printf("The threads couldn't be detached\n");
        exit(EXIT_FAILURE);
    }

    pthread_exit(NULL);

    exit(EXIT_SUCCESS);
}

// скомпилировать с ключом -g
// запустить профилировщик:
// $ vargrind ./45-stack-vars.c

// попробовать несолько раз, на какой-то раз сообщит о проблемах 
