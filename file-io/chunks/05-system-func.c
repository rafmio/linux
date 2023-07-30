#include <stdio.h>
#include <stdlib.h>

int main() {
	char *cmd = "ls -la ";
	char *dirProc = "/proc/";
	char *fullCmd = (char*)malloc(sizeof(cmd) + sizeof(dirProc));
	sprintf(fullCmd, "%s%s", cmd, dirProc);
	printf("fullCmd: %s\n", fullCmd);

	system(fullCmd);

	free(cmd);
	free(dirProc);
	free(fullCmd);

	return 0;
}
