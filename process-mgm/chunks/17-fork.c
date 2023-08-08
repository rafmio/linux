// https://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/fork/create.html
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#ifndef MAX_COUNT
#define MAX_COUNT 40
#endif

#ifndef BUF_SIZE
#define BUF_SIZE 64
#endif

int
main() {
    pid_t   pid;
    int     i;
    char    buf[BUF_SIZE]; 

    pid = fork();
    for (i = 1; i <= MAX_COUNT; i++ ) {
        sprintf(buf, "This line is from pid %d, value = %d\n", pid, i);
        write(STDOUT_FILENO, buf, strlen(buf));
    }
}

/*
What is the reason of using write rather than printf? 
It is because printf() is "buffered," meaning printf() will group the output 
of a process together. While buffering the output for the parent process, 
the child may also use printf to print out some information, 
which will also be buffered. As a result, since the output will not be send to 
screen immediately, you may not get the right order of the expected result. 
Worse, the output from the two processes may be mixed in strange ways. 
To overcome this problem, you may consider to use the "unbuffered" write.
*/