#include <stdio.h>      // perror
#include <stdlib.h>     // exit 
#include <unistd.h>     // write, read, (u)sleep, close
#include <fcntl.h>      // open, sem_open (oflag)
#include <sys/mman.h>   // mman: memory manager -- mmap()
#include <semaphore.h>

#define TEMP "temp"
#define SEM_NAME "/my_named_sem"

int main()
{
    const int zero = 0;
    sem_t *p_sem;

    int fd = open(TEMP, O_RDWR|O_CREAT, S_IRWXU);
    write(fd, &zero, sizeof(int*));
    int *p_fd = mmap(NULL, sizeof(int*),
	     PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    if ((p_sem = sem_open(SEM_NAME, O_CREAT, 0600, 1)) == SEM_FAILED) {
	perror("sem_open");
	exit(1);
    }

    if (fork() == 0) {  // child process
	for (int i = 0; i < 5; ++i) {
	    sem_wait(p_sem);
	    printf("child: %d\n", *p_fd);
	    (*p_fd)++;
	    usleep(10);
	    printf("child end\n");
	    sem_post(p_sem);
	    usleep(10);
	}
    } else {            // parent process
	for (int i = 0; i < 5; ++i) {
	    sem_wait(p_sem);
	    printf("parent: %d\n", *p_fd);
	    (*p_fd)++;
	    usleep(10);
	    printf("parent end\n");
	    sem_post(p_sem);
	    usleep(10);
	}
    }
    sem_close(p_sem);
    sem_unlink(SEM_NAME);
    remove(TEMP);
    return 0;
}
