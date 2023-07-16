#include <unistd.h>
#include <stdio.h>

void main() {
    int ret;
    ret = execl("/bin/vi", "vi", "./ps.go");
    if (ret == -1) {
        perror("execl");
    }
}