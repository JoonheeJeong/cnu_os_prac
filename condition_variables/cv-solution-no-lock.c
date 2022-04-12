#include <stdio.h>
#include <pthread.h>

#define LIMIT 100000 // 10만

int counter = 0;
pthread_mutex_t mutex_counter = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_counter = PTHREAD_COND_INITIALIZER;

void work1()
{
    while (counter != LIMIT)
	counter++;
    printf("child: work1 done\n");
}

void *child(void *arg) 
{
    printf("child: begin\n");

    work1();
    pthread_cond_signal(&cond_counter);

    printf("child: return\n");
    return 0;
}

int main()
{
    pthread_t t1;

    printf("parent: begin\n");
    pthread_create(&t1, NULL, child, NULL);

    while (counter != LIMIT)
	pthread_cond_wait(&cond_counter, &mutex_counter);
    printf("counter: %d\n", counter);

    printf("parent: return\n");
    return 0;
}
