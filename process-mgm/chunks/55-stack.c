// Код не является потокобезопасным, может выдавать ошибки
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

int* shared_int;

void*
t1_body(void* arg) {
    printf("t1_body, arg: %p\n", arg);
    int local_var = 100;
    shared_int = &local_var; // local_var - в стеке данного потока, м.б. сбой
    // ждем, пока другой поток не выведет разеляемое целое значение
    usleep(10);
    return NULL;
}

void*
t2_body(void* arg) {
    printf("t2_body, arg: %p\n", arg);
    printf("%d\n", *shared_int);
    return NULL;
}

int
main() {
    shared_int = NULL;

    pthread_t t1;
    pthread_t t2;

    pthread_create(&t1, NULL, t1_body, NULL);
    pthread_create(&t2, NULL, t2_body, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}

