// https://www.geeksforgeeks.org/signals-c-language/
#include <stdio.h>
#include <signal.h>

int main() {
    signal(SIGINT, handle_sigint);
}