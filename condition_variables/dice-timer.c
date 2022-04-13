#include <stdio.h>
#include <pthread.h>
#include <stdlib.h> // rand, srand
#include <time.h> // time
#include <unistd.h> // usleep

#define NLOOPS 1

int num = 0;
int generated = 0;
//pthread_mutex_t mutex_num = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_gen = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_gen = PTHREAD_COND_INITIALIZER;

void *child(void *arg) 
{
    printf("child: begin\n");
    srand(time(NULL));
    for (int i = 0; i < NLOOPS; ++i) {
	pthread_mutex_lock(&mutex_gen);
//	pthread_mutex_lock(&mutex_num);
	num = (rand() % 6) + 1;
	generated = 1;
	pthread_cond_signal(&cond_gen);
//	pthread_mutex_unlock(&mutex_num);
	pthread_mutex_unlock(&mutex_gen);
	sleep(1);
    }

    printf("child: return\n");
    return NULL;
}

int main()
{
    pthread_t t1;
    printf("parent: begin\n");
    pthread_create(&t1, NULL, child, NULL);

    for (int i = 0; i < NLOOPS; ++i) {
	pthread_mutex_lock(&mutex_gen);
	while (!generated)
	    pthread_cond_wait(&cond_gen, &mutex_gen);
//	pthread_mutex_lock(&mutex_num);
	printf("parent: %d\n", num);
	generated = 0;
//	pthread_mutex_unlock(&mutex_num);
	pthread_mutex_unlock(&mutex_gen);
    }
//    pthread_join(t1, NULL);
    printf("parent: return\n");
    return 0;
}
