#include "tlpi_hdr.h"

int main(int argc, char *argv[]) {
	int j;
	for (j = 0; j < argc; j++ ) {
		printf("argv[%d] = %s\n", j, argv[j]);	
	}

	FILE *fp;
	char buffer[1024];

	fp = fopen("/proc/self/cmdline", "r"); // как оказалось - не выводит argc и argv
	if (fp == NULL) {
		printf("error opening\n");
		return 1;	
	} else {
		printf("file opening: success\n");	
	}

	printf("output /proc/self/cmdline:\n");
	while(fgets(buffer, sizeof(buffer), fp) != NULL) {
		printf("%s", buffer);	
	}

	fclose(fp);
	printf("\n");

	exit(EXIT_SUCCESS);
}
