#include <stdio.h>      // perror
#include <stdlib.h>     // exit 
#include <unistd.h>     // write, read, (u)sleep, close
#include <sys/stat.h>   // open, sem_open
#include <fcntl.h>      // open, sem_open (mode, flag)
#include <sys/mman.h>   // mman: memory manager -- mmap()
#include <semaphore.h>

int main()
{
    const int nloop = 5;
    const int zero = 0;
    int fd;
    int *p_fd;
    int i;
    sem_t *p_sem;

    fd = open("log.txt", O_RDWR|O_CREAT, S_IRWXU);
    write(fd, &zero, sizeof(int));
    p_fd = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    sem_unlink("my_sem");
    if ((p_sem = sem_open("my_sem", O_CREAT, 0600, 1)) == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    if (fork() == 0) {  // child
        for (i = 0; i < nloop; ++i) {
            sem_wait(p_sem);
            printf("child: %d\n", *p_fd);
            (*p_fd)++;
            usleep(100);
            printf("child end\n");
            sem_post(p_sem);
            usleep(100);
        }
    } else {            // parent
        for (i = 0; i < nloop; ++i) {
            sem_wait(p_sem);
            printf("parent: %d\n", *p_fd);
            (*p_fd)++;
            usleep(100);
            printf("parent end\n");
            sem_post(p_sem);
            usleep(100);
        }
    }
    sem_close(p_sem);
    return 0;
}
