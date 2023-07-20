#include <stdio.h>
#include <unistd.h>

void main() {
	int ret;
	ret = execl("/bin/ps", "ps", NULL);
	if (ret == -1) {
		perror("execl");	
	}
	printf("ret: %d\n", ret);
	printf("PID:%d\n", (__intmax_t) getpid());
}
