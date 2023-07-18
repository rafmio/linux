#include <stdio.h>
#include <unistd.h>

int
main(void) {
    void *stack_addr = __builtin_frame_address(0);
    printf("Stack top's addres: %p\n", stack_addr);

    return 0;
}