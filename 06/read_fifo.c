#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_PATH "./fifo_temp"
#define BUF_SIZE 100

int main()
{
    int cnt = 0;
    int fd;
    char buf[BUF_SIZE];

    mkfifo(FIFO_PATH, 0600);
    fd = open(FIFO_PATH, O_RDONLY);
    while(1) {
        memset(buf, 0, BUF_SIZE);
        read(fd, buf, BUF_SIZE);
        printf("%d: %s", ++cnt, buf);
    }
    close(fd);
    return 0;
}

