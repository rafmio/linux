// Программу можно запустить как с одним аргументом, так и без
#define _GNU_SOURCE
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
// #include <sys/types.h>
#include <fcntl.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#ifndef CHILD_SIG
#define CHILD_SIG SIGUSR1   // при завершении клонированного потомка
                            // будет сгенерирован сигнал 
#endif

static int                  // начальная ф-ция для клонированного потомка
childFunc(void *arg) {
    if (close(*((int *) arg)) == -1) {
        perror("close()");
        exit(EXIT_FAILURE);
    }

    printf("Inside childFunc(): the child's PID: %d, PPID: %d\n", getpid(), getppid());
    
    return 0;               // здесь потомок завершается
}

int
main(int argc, char *argv[]) {
    if (argc > 1) {
        printf("\nargv[1]: %s\n", argv[1]);
    }

    printf("I'm a parent. My PID is: %d\n", getpid());
    const int STACK_SIZE = 65536;   // Размер стека для клонированного потомка
    char *stack;                    // Начало буфера стека
    char *stackTop;                 // Конец буфера стека
    int s, fd, flags;

    fd = open("/dev/null", O_RDWR); // потомок закроет дескриптор fd
    if (fd == -1) {
        perror("open /dev/null");
        exit(EXIT_FAILURE);
    }

    /* Если argc > 1, потомок будет разделять таблицу файловых дескрипторов с родителем*/
    flags = (argc > 1) ? CLONE_FILES : 0;  // CLONE_FILES - битовая маска

    /* Выделяем стек для потомка */
    stack = malloc(STACK_SIZE);
    if (stack == NULL) {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }
    stackTop = stack + STACK_SIZE;      // Предполагается, что стек растет снизу вверх

    /*
    Игнорируем CHILD_SIG, если это сигнал, кот. по умолчанию завершает процесс.
    При этом не игнорируем SIGCHLD (кот. игнорируется по умолчанию), иначе это
    могло бы помешать созданию процесса-"зомби". 
    */

   if (CHILD_SIG != 0 && CHILD_SIG != SIGCHLD) {
    if (signal(CHILD_SIG, SIG_IGN) == SIG_ERR) {
        perror("signal()");
        exit(EXIT_FAILURE);
    }
   }

   /*
    Создаем потомка, потомок начинает выполнение childFunc()
   */
    if ( clone(childFunc, stackTop, flags | CHILD_SIG, (void*) &fd) == -1 ) {
        perror("clone()");
        exit(EXIT_FAILURE);
    }
    // Родитель переходит сюда и ждет потомка. Потомку, который применяет 
    // для уведомления любой сигнал, кроме SIGCHLD, нужно значениее _WCLONE

    if ( waitpid(-1, NULL, (CHILD_SIG != SIGCHLD) ? __WCLONE : 0) == -1) {
        perror("waitpid()");
        exit(EXIT_FAILURE);
    }
    printf("child has terminated\n");

    // Повлияло ли на родителя закритие дескриптора в потомке?

    s = write(fd, "x", 1);
    if ( s == -1 && errno == EBADF ) {
        printf("file descriptor %d has been closed\n", fd);
    } else if (s == -1) {
        printf("write() on file descriptor %d failed", fd);
    } else {
        printf("write() on file descriptor %d succeeded\n", fd);
    }

    exit(EXIT_FAILURE);
}


