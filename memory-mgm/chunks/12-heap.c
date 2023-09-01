#include <stdio.h>
#include <stdlib.h>

int globalIntUnInitialized;
int globalIntInitialized = 512;

void print_mem_maps()
{
#ifdef __linux__
    FILE *fd = fopen("/proc/self/maps", "r");
    if (!fd)
    {
        perror("Could not open maps file");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("\nthe file has opened\n");
    }

    char line[1024];
    while (!feof(fd))
    {
        fgets(line, 1024, fd);
        printf("> %s", line);
    }
    fclose(fd);
#endif
}

void print_var_addresses() {
    int localIntUninitialized;
    int localIntInitialized = 1023;
    static int localStatIntUn;
    static int localStatIntIn = 4094;

    printf("\n\n");

    printf("global int uninitialized: %p\n", (void*)&globalIntUnInitialized);
    printf("global int initialized:   %p\n", (void*)&globalIntInitialized);
    printf("local int uninitialized:  %p\n", (void*)&localIntUninitialized);
    printf("local int initialized:    %p\n", (void*)&localIntInitialized);
    printf("local static int uninit:  %p\n", (void*)&localStatIntUn);
    printf("local static int init:    %p\n", (void*)&localStatIntIn);

    printf("\n");
}

int main()
{
    // выделяем 10 байт памяти без инициализации
    char *ptr1 = (char *)malloc(10 * sizeof(char));
    printf("Address of ptr1: %p\n", (void *)&ptr1);
    printf("Memory allocated by malloc at %p: ", (void *)ptr1);
    for (int i = 0; i < 10; i++)
    {
        ptr1[i] = i + 1;
        printf("0x%02x ", (unsigned char)ptr1[i]);
    }
    printf("\n");

    // выделяем 10 байт, каждый из которых обнулен
    char *ptr2 = (char *)calloc(10, sizeof(char));
    printf("Address of ptr2: %p\n", (void *)&ptr2);
    printf("Memory allocated by calloc at %p: ", (void*)ptr2);
    for (int i = 0; i < 10; i++)
    {   
        ptr2[i] = i * i;
        printf("0x%02x ", (unsigned char)ptr2[i]);
    }
    printf("\n");

    print_mem_maps();

    free(ptr1);
    free(ptr2);

    print_var_addresses();

    return 0;
}

/*
$ vargrind --leak-check=full ./12-heap.c
*/