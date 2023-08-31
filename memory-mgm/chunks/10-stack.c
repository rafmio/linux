#include <stdio.h>

int main(int argc, char **argv) {
    char arr[4];
    arr[0] = 'A';
    arr[1] = 'B';
    arr[2] = 'C';
    arr[3] = 'D';
    return 0;
}

/*
Память, необходимая для arr, выделяется в стеке, а не в куче, потому, что мы 
не используем malloc.
В стеке по умолчанию выделяются все переменные и массивы.
*/

/*
(gdb) break main
*/




// gcc -g 10-stack.c -o 10-stack.exe