#include <fcntl.h> // open
#include <stdio.h> // perror, fgets
#include <stdlib.h> // exit
#include <string.h> // strlen, memset
#include <unistd.h> // close, write

#define BUF_SIZE 64
#define PATHNAME "./fifo_special"

int main()
{
    int fd, rc;
    char buf[BUF_SIZE];

    if ((fd = open(PATHNAME, O_WRONLY)) == -1) {
	perror("open");
	exit(1);
    }

    while (1) {
	memset(buf, 0, BUF_SIZE);
	fgets(buf, BUF_SIZE, stdin);
	rc = write(fd, buf, strlen(buf)+1);
	if (rc == -1) {
	    perror("write");
	    close(fd);
	    exit(1);
	} else if (rc == BUF_SIZE && buf[BUF_SIZE - 2] != '\n') {
	    printf("buffer overflow.\n");
	    break;
	}
    }
    close(fd);

    return 0;
}
