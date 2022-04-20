#include <fcntl.h> // open
#include <stdio.h> // perror
#include <stdlib.h> // exit
#include <string.h> // memset
#include <sys/stat.h> // mkfifo
#include <unistd.h> // close, read
#include <pthread.h>
#include <semaphore.h>

#define BUF_SIZE 64
#define RECV_PATH "./fifo1"
#define SEND_PATH "./fifo2"

int recv_fd, send_fd;
char rbuf[BUF_SIZE];
char wbuf[BUF_SIZE];
pthread_t t1, t2;

int any_exit = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void *recv(void *arg)
{
    int rc, cnt = 0;

    mkfifo(RECV_PATH, 0600);
    recv_fd = open(RECV_PATH, O_RDONLY);

    while (1) {
	memset(rbuf, 0, BUF_SIZE);
	rc = read(recv_fd, rbuf, BUF_SIZE);
	if (rc == 0 || (rbuf[0] != '\n' && rbuf[1] == '\0')) {
	    printf("EOF(eod-of-file).\n");
	    break;
	} else if (rc == BUF_SIZE && rbuf[BUF_SIZE - 2] != '\n') {
	    printf("rbuffer overflow.\n");
	    break;
	}
	printf("%d(%d): %s", ++cnt, rc, rbuf);
    }
    any_exit = 1;
    pthread_cond_signal(&c);
    return NULL;
}

void *send(void *arg)
{
    int rc;

    mkfifo(SEND_PATH, 0600);
    send_fd = open(SEND_PATH, O_WRONLY);

    while (1) {
	memset(wbuf, 0, BUF_SIZE);
	fgets(wbuf, BUF_SIZE, stdin);
	rc = write(send_fd, wbuf, strlen(wbuf)+1);
	if (rc == BUF_SIZE && wbuf[BUF_SIZE - 2] != '\n') {
	    printf("wbuffer overflow.\n");
	    break;
	}
    }
    any_exit = 1;
    pthread_cond_signal(&c);
    return NULL;
}

int main()
{
    pthread_create(&t1, NULL, recv, NULL);
    pthread_create(&t2, NULL, send, NULL);
    pthread_mutex_lock(&m);
    while (!any_exit)
	pthread_cond_wait(&c, &m);
    pthread_mutex_unlock(&m);
    pthread_cancel(t1);
    pthread_cancel(t2);
    close(recv_fd);
    remove(RECV_PATH);
    close(send_fd);
    remove(SEND_PATH);
    return 0;
}
