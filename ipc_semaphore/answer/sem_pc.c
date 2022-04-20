#include <stdio.h>
#include <pthread.h>
#include <unistd.h>     // usleep (micro sleep)
#include <semaphore.h>

#define MAX 10 
#define PROD_SIZE 3
#define CONS_SIZE 7
#define PROD_ITEM 5
#define CONS_ITEM 2

sem_t id_lock, sem_prod, sem_cons, cnt_lock;

int buffer[MAX]; // ! buffer is circular queue !
int count = 0;
int get_ptr = 0;
int put_ptr = 0;
int prod_id = 1;
int cons_id = 1;

int get()
{
    if (count == 0)
	return -1;
    int ret = buffer[get_ptr];
    get_ptr = (get_ptr + 1) % MAX;
    count--;
    return ret;
}

int put(int val)
{
    if (count == MAX)
	return -1;
    buffer[put_ptr] = val;
    put_ptr = (put_ptr + 1) % MAX;
    count++;
    return val;
}

void *producer(void *arg)
{
    sem_wait(&id_lock);
    int id = prod_id++;
    sem_post(&id_lock);
    for (int i = 0; i < PROD_ITEM; ++i) {
//	usleep(10);
	sem_wait(&sem_prod);
	sem_wait(&cnt_lock);
	int ret = put(i);
	if (ret == -1)
	    printf("can't put, becuase buffer is full.\n");
	else
	    printf("producer %d PUT %d\n", id, ret);
	sem_post(&cnt_lock);
	sem_post(&sem_cons);
    }
    return NULL;
}

void *consumer(void *arg)
{
    sem_wait(&id_lock);
    int id = cons_id++;
    sem_post(&id_lock);
    for (int i = 0; i < CONS_ITEM; ++i) {
//	usleep(10);
	sem_wait(&sem_cons);
	sem_wait(&cnt_lock);
	int ret = get();
	if (ret == -1)
	    printf("can't get, becuase buffer is empty.\n");
	else
	    printf("consumer %d GET %d\n", id, ret);
	sem_post(&cnt_lock);
	sem_post(&sem_prod);
    }
    return NULL;
}

int main()
{
    pthread_t prod[PROD_SIZE];
    pthread_t cons[CONS_SIZE];

    sem_init(&id_lock, 0, 1);
    sem_init(&sem_prod, 0, MAX);
    sem_init(&sem_cons, 0, 0);
    sem_init(&cnt_lock, 0, 1);

    for (int i = 0; i < PROD_SIZE; ++i)
	pthread_create(&prod[i], NULL, producer, NULL);
    for (int i = 0; i < CONS_SIZE; ++i)
	pthread_create(&cons[i], NULL, consumer, NULL);

    for (int i = 0; i < PROD_SIZE; ++i)
	pthread_join(prod[i], NULL);
    for (int i = 0; i < CONS_SIZE; ++i)
	pthread_join(cons[i], NULL);

    sem_destroy(&id_lock);
    sem_destroy(&sem_prod);
    sem_destroy(&sem_cons);
    sem_destroy(&cnt_lock);

    return 0;
}
