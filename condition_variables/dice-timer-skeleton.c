#include <stdio.h>
#include <pthread.h>
#include <stdlib.h> // rand, srand
#include <time.h> // time
#include <unistd.h> // usleep

#define NLOOPS 5

int num = 0;
int generated = 0;
pthread_mutex_t mutex_num = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_gen = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_gen = PTHREAD_COND_INITIALIZER;

void *child(void *arg) 
{
    printf("child: begin\n");
        /* TODO */
        /*------*/
        /* TODO */
    printf("child: return\n");
    return 0;
}

int main()
{
    pthread_t t1;
    printf("parent: begin\n");
        /* TODO */
        /*------*/
        /* TODO */
    printf("parent: return\n");
    return 0;
}
