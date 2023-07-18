#include <stdio.h>
#include <stdlib.h>

char globBuff[65536];   // Сегмент неинициализированных данных
int primes[] = { 2, 3, 5, 7 };  // Сегмент инициализированных данных

static int
square(int x)       // Размещается во фрейме для square
{
    int result;     // Размещается во фрейме для square
    result = x * x;
    return result;  // Возвращаемое значение передается через регистр
}

static void
doCalc(int val)     // Размещается во фрейме для doCalc()
{
    printf("The square of %d is %d\n", val, square(val));
    if (val < 1000) {
        int t;      // Размещается во фрейме для doCalc()
        t = val * val * val;
        printf("The cube of %d is %d\n", val, t);
    }
}

int
main(int argc, char *argv[])    // Размещается во фрейме для main()
{
    static int key = 9973;  // Сегмент инициализированных данных
    static char mbuf[10240000]; // Сегмерт неинициализированных данных
    char *p;                // Размещается во фрейме для main()
    p = malloc(1024);       // Указывает на память в сегменте кучи
    doCalc(key);
    exit(EXIT_SUCCESS); 
}