//#include "tlpi_hdr.h"
#include <stdlib.h> // for **environ
#include <stdio.h>
#include <unistd.h> // for getenv()


extern char **environ;
int
main(int argc, char *argv[]) {
	char **ep;
	for(ep = environ; *ep != NULL; ep++) {
		puts(*ep);	
	}

	printf("\n\nUsing getenv():\n");

	char *path = getenv("PATH");
	char *user = getenv("USER");

	printf("$PATH: %s\n", path);
	printf("$USER: %s\n", user);
	
	exit(EXIT_SUCCESS);
}

