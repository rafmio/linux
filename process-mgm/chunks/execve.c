#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void main() {
   int pid;
   char* args[] = {"execl.exe"}; // в массиве всего один элемент - один аргумент
   pid = fork();
   if (pid < 0) {
    perror("fork() failed");
   } else if (pid == 0) { /*Child*/
       execve("/bin/ls", args, NULL);
       perror("/bin/ls execve() failed"); 
   } else { /*Parent*/
       wait(NULL);
       printf("Child exited with code: %d\n", WEXITSTATUS(pid));
   }
}