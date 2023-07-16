#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

pid_t getpid(void);

void main() {
    printf("My pid = %jd\n", (__intmax_t) getpid());
    printf("Parent's pid = %jd\n", (__intmax_t) getppid()); 
}
