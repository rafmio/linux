// Программа, демонстрирующая переполнение буфера
#include <stdio.h>
#include <string.h>
 
int main(int argc, char ** argv) {
    if (argc != 2) {
        printf("Too few arguments\n");
        return 1;
    }
    char str[10];
    strcpy(str, argv[1]);
    printf("Hello, %s!\n", str);
}

/*
Этот код не проверяет содержимое и размер argv[1], копируя содержимое прямо в
массив str, выделенный на вершине стека

Может привести к вредоносной атаке
*/