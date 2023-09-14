#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

static int idata = 111;  // выделена в сегменте данных

int 
main(int argc, char *argv[]) {
    int istack = 222;   // в сегменте стека
    pid_t childPid;

    // в книге Керриска сказано, что иногда fork() вызывают так (через switch)
    switch ( childPid = fork()) {
        case -1:
            perror("fork()");
        case 0:
            idata *= 3;
            istack *= 3;
            break;
        default:
            printf("childPid: %d\n", childPid);
            sleep(3);       // даём потомку шанс выполниться
            break;
    }

    // Здесь выполняются потомок и родитель
    printf("PID=%ld %s idata=%d istack=%d\n", (long)getpid(), 
    (childPid == 0) ? "(child)" : "(parent)", idata, istack);

    exit(EXIT_SUCCESS);
}

/*
Программа создает дочерний процесс, который изменяет унаследованные им в результате 
вызова fork() глобальные и автоматические переменные
*/