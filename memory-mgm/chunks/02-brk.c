#include <stdio.h>
#include <unistd.h>

int
main() {
    long int page_size = sysconf(_SC_PAGE_SIZE);
    printf("My pagesize: %ld\n", page_size);

    void* c1 = sbrk(0);
    printf("program break address: %p\n", c1);

    c1 = (void*)( (char*) c1 + 1);
    printf("c1: %p\n", c1);
    brk(c1);

    void* c2 = sbrk(0);
    printf("program break address: %p\n", c2);

    return 0;
}