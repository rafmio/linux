// gcc -o 40-pthread.exe 40-pthread.c -pthread

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int count;                                  // общие данные для потоков
int atoi(const char *nptr);
void *potok(void *param);                   // потоковая функция

int main(int argc, char *argv[]) {
    pthread_t tid;                          // id потока
    pthread_attr_t attr;                    // аттрибуты потока

    if (argc != 2) {
        fprintf(stderr, "usage: progtest <integer value>\n");
        return -1;
    }

    if (atoi(argv[1]) < 0) {
        fprintf(stderr, "Argument %d cannot be negative!", atoi(argv[1]));
        return -1;
    }

    pthread_attr_init(&attr);               // получаем дефолтные значения атрибутов
    
    pthread_create(&tid, &attr, potok, argv[1]); // create a new thread

    pthread_join(tid, NULL);                // waiting for thread's finishing 

    printf("count = %d\n", count);


}


void *potok(void *param) {
    int i;
    int upper = atoi(param);
    unsigned int TID;
    TID = pthread_self();
    printf("TID: %d\n", TID);
    printf("PID: %d, PPID: %d\n", getpid(), getppid());
    if (upper > 0) {
        for (i = 1; i <= upper; i++) {
            count += i;
        }
    }

    pthread_exit(0);
}