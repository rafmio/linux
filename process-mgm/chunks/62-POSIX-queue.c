#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <mqueue.h>

int
main() {
    // обработчик очереди сообщений
    mqd_t mq;

    struct mq_attr attr;
    attr.mq_flags   = 0;
    attr.mq_maxmsg  = 10;
    attr.mq_msgsize = 32;
    attr.mq_curmsgs = 0;

    int childPid = fork();
    if (childPid == -1) {
        fprintf(stderr, "fork() error\n");
        exit(1);
    } 

    if (childPid == 0) {
        // потомок ждет, пока родитель создаст очередь
        sleep(1);
        mqd_t mq = mq_open("/mq0", O_WRONLY);
        char str[] = "Hello Daddy!";

        // потомок записывает в fd, открытый для записи
        fprintf(stdout, "CHILD: Waiting for 2 seconds...\n");
        sleep(2);
        fprintf(stdout, "CHILD: Writing to daddy...\n");
        mq_send(mq, str, strlen(str) + 1, 0);
        mq_close(mq);
    } else {
        mqd_t mq = mq_open("/mq0", O_RDONLY | O_CREAT, 0644, &attr);
        char buff[32];
        fprintf(stdout, "PARENT: Reading from child...\n");
        int num_of_read_bytes = mq_receive(mq, buff, 32, NULL);
        fprintf(stdout, "PARENT: Received from child: %s\n", buff);
        mq_close(mq);
        mq_unlink("/mq0");
    }

    return 0;
}