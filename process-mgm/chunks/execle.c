#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(void) { 
	char *args[] = {"/bin/echo", "Hello, World!", NULL}; 
	execle("/bin/echo", "/bin/echo", "Hello, World!","",(char*)0,(char*)0); 
	return 0; 
}