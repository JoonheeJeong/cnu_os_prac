#include <fcntl.h> // open
#include <stdio.h> // perror
#include <stdlib.h> // exit
#include <string.h> // memset
#include <sys/stat.h> // mkfifo
#include <unistd.h> // close, read

#define BUF_SIZE 64
#define FIFO_PATH "./fifo_special"

int main()
{
    int rc, fd, cnt = 0;
    char buf[BUF_SIZE];

    if ((fd = open(FIFO_PATH, O_RDONLY)) == -1) {
	mkfifo(FIFO_PATH, 0600);
	fd = open(FIFO_PATH, O_RDONLY);
    }

    while (1) {
	memset(buf, 0, BUF_SIZE);
	rc = read(fd, buf, BUF_SIZE);
        if (rc == -1) {
	    perror("read");
	    close(fd);
	    exit(1);
	} else if (rc == 0 || (buf[0] != '\n' && buf[1] == '\0')) {
	    printf("EOF(eod-of-file).\n");
	    break;
	} else if (rc == BUF_SIZE && buf[BUF_SIZE - 2] != '\n') {
	    printf("buffer overflow.\n");
	    break;
	}
	printf("%d(%d): %s", ++cnt, rc, buf);
    }
    close(fd);

    return 0;
}
