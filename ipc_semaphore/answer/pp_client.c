#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

#define FIFO_PATH "fifo_temp"
#define SEM_NAME "/sem_pp"
#define BUF_SIZE 8
#define TURN 5

int main()
{
    const char *msg = "pong\n";
    int fd;
    int score = 100;
    sem_t *p_sem;
    char buf[BUF_SIZE];

    fd = open(FIFO_PATH, O_RDWR);
    p_sem = sem_open(SEM_NAME, 0);
    for (int i = 0; i < TURN; ++i) {
	sem_wait(p_sem);
	read(fd, buf, BUF_SIZE);
	printf("[opponent] %sYour turn!\n", buf);
	fgets(buf, BUF_SIZE, stdin);
	if (strcmp(buf, msg) != 0) {
	    printf("wrong! -20\n");
	    score -= 20;
	}
	write(fd, buf, strlen(buf)+1);
	sem_post(p_sem);
	sleep(1);
    }
    printf("Done! Your score: %d\n", score);
    return 0;
}
