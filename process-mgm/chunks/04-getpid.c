#include <sys/types.h> // можно и не импортировать, если getpid() закомменчен
#include <unistd.h>
#include <stdio.h>

pid_t getpid(void); // можно и закомментировать или удалить - все равно работает

int main() {
    printf("My pid = %jd\n", (__intmax_t) getpid());
    printf("Parent's pid = %jd\n", (__intmax_t) getppid()); 

    return 0;
}
