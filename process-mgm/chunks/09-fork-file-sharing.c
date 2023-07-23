#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int fd, flags;
    char template[] = "/tmp/testXXXXXX";

    setbuf(stdout, NULL); // отключаем буферзацию stdout
    fd = mkstemp(template); // create a unique temporary file 
    if(fd == -1) {
        perror("mkstemp")
    }
}