#include <stdio.h>
#include <unistd.h>

// extern char etext, edata, end;

int
main(void) {
    void *stack_addr = __builtin_frame_address(0);
    printf("Stack top's addres:       %10p\n", stack_addr);

    // printf("Program text (etext)      %10p\n", &etext);
    // printf("Initialized data (edata)  %10p\n", &edata);
    // printf("Unitialized data (end)    %10p\n", &end);


    return 0;
}