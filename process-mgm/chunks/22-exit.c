#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    printf("Hello-mello, Kissy-Missy\n");
    write(STDOUT_FILENO, "Ciao\n", 5);
    
    if ( fork() == -1 ) {
        perror("fork()");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

/*
Разные результаты:

$ ./22-exit.exe
Hello-mello, Kissy-Missy
Ciao

$ ./22-exit.exe > outputFd
$ cat outputFd
Ciao
Hello-mello, Kissy-Missy
Hello-mello, Kissy-Missy

    Буферы stdio находятся в пользовательском пространстве памяти процесса.
    Следовательно эти буферы дублируются в дочернем процессе вызовом fork().
    Когда stdout направлен в терминал, буферизация в нем по умолчанию
происходит построчно, благодаря чему, строки, разделенные разрывами, сразу
выводятся вызовом printf()
    Однако stdout, направленный в файл, по умолчанию буферизируется по блокам.
    Т.о. на момент вызова fork() строка, выводимая вызовом printf() все еще 
    находится в родит-м буфере stdio и, следовательно, дублируется в потомке.

    Когда род.и дочерн. процессы вызывают exit(), ни оба сбрасывают свои копии 
буферов stdio, что приводит к дубрилованию результата. 

    Решение, чтоб избежать этого:
        - перед fork() использовать fflush(), кот.сбрасывает соотв-щий буфер.
          Или как вариант, можно отключить буферизацию потока stdio
          с пом. setvbuf() или setbuf()
        - потомок может вызывать _exit(), а не exit(), чтобы не сбрасывать буферы
          stdio. Этот метод иллюстрирует общее правило: в приложении, создающем 
          потомка, кот.не выполняет новой прог-мы, обычно только один из пр-ссов
          (чаще всего родитель) долж.заверш-ся с пом. exit(), тогда как для остальных
          следует использ. _exit().
          Это дает гарантию того, что только один пр-сс вызывает обработчики выхода и
          сбрасывает буферы stdio

    Вывод вызова write() в программе не дублируется, т.к. данные этого вызова 
передаются напрямую в буфер ядра, кот.не подлежит копированию во время выполнения fork()
Текст из вызова write() появляется раньше, т.к. он сразу же доставляется в кэш буфера 
ядра, тогда как данные при вызова printf() передаются только в результате сбрасывания
буферов stdio вызовом exit()
*/