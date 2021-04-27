#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_PATH "fifo_temp"
#define SEM_NAME "sem_pp"
#define BUF_SIZE 8
#define TURN 5


int main()
{
    const char *msg = "ping\n";
    int fd;
    int cnt;
    int score = 100;
    sem_t *p_sem;
    char buf[BUF_SIZE];

    /*
       Homework
       Fill your codes here and make the correct result.
       Refer to the included header files and given variables.
       You can complete this file from this skeleton without creating another variable,
       but also modify anything as you want.
       As long as your result is correct, it doesn't matter how you write codes.
       However, you must use fifo, named semaphore.

       And based on this file, you have to create another source for the client.
       It would be similar to this.
    */

    printf("Done! Your score: %d\n", score);
    return 0;
}
