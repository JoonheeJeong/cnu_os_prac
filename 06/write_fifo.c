#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define BUF_SIZE 100
#define FIFO_PATH "./fifo_temp"

int main()
{
    int cnt = 0;
    int fd;
    char buf[BUF_SIZE];

    fd = open(FIFO_PATH, O_WRONLY);
    while(1) {
        memset(buf, 0, BUF_SIZE);
        fgets(buf, BUF_SIZE, stdin);
        write(fd, buf, strlen(buf));
    }
    close(fd);
    return 0;
}
