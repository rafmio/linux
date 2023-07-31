#include <stdio.h>
#include <unistd.h>

int
main(void) {
	char *binaryPath = "/bin/bash";
	char *const args[] = {binaryPath, "-c", "echo \"Visit $HOSTNAME:$PORT from your browser.\"", NULL};
	char *const env[] = {"HOSTNAME=www.linuxhint.com", "PORT=8080", NULL};

	execve(binaryPath, args, env);

}

/*
Флаг -c (–command) в командной строке bash позволяет выполнить указанную команду вместо запуска программы, которая обычно запускается при выполнении команды. Например, если вы хотите запустить команду ls -la в терминале, вы можете использовать флаг -c, чтобы выполнить эту команду вместо запуска команды ls:

$ bash -c “ls -la”

Это может быть полезно в некоторых случаях, когда вы хотите выполнить определенную команду без запуска программы.
*/
