#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    void *ptr = mallo(1024);  //  выделяем для кучи 1 КБайт
    printf("Address: %p\n", ptr);
    fflush(stdout);           // для принудительного вывода

    // бесконечный цикл
    while (1) {
        sleep(1);   // засыпаем на 1 секунду
    };

    return 0;
}