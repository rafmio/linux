// Обычно wait() применяется только для обмена информацией о завершении пр-сса
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int status;
    pid_t pid;

    // Попробовать разные варианты развершения (return, abort())
    if ( !fork() ) 
        // return 1;
        abort();

    pid = wait(&status);
    if ( pid == -1 ) {
        perror("wait");
    }

    printf("pid = %d\n", pid);
    printf("\nstatus: %d\n", status);

    if ( WIFEXITED (status) )
        printf("Normal exiting, status = %d\n", WEXITSTATUS(status));
    if ( WIFSIGNALED (status) )
        printf("Killed by signal = %d\n", WTERMSIG(status));
    if ( WIFSTOPPED(status) )
        printf("Stopped by signal = %d\n", WSTOPSIG(status));
    if ( WIFCONTINUED (status) )
        printf("Continued\n");


    return 0;    
}
