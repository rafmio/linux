#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Too few arguments. Usage: '$ %s <fileName>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE* file;
    file = fopen(argv[1], "w+");
    int fputsRes = fputs("Hey! Let's write some text!", file);
    printf("fputsRes: %d\n", fputsRes);

    int fseekRes = fseek(file, 10, SEEK_END); 
    printf("fseekRes: %d\n", fseekRes);
    fputsRes = fputs("This text was wrote 10 bytes right from EOF\n", file);
    printf("fputsRes: %d\n", fputsRes);

    fprintf(file, "Hello, Tosy-Bosy, wrote via fprintf()\n");

    fclose(file);
}