#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAN 5

int key = 4;
int lock = 1;
sem_t sem, ordering;

void use()
{
    sem_wait(&sem);
    sem_wait(&ordering);
    key--;
    printf("%u In (key:%d)\n", (unsigned) pthread_self(), key);
    sem_post(&ordering);
    usleep(100);
    sem_wait(&ordering);
    key++;
    printf("%u Out (key:%d)\n", (unsigned) pthread_self(), key);
    sem_post(&ordering);
    sem_post(&sem);
}

int main()
{
    pthread_t man[MAN];

    sem_init(&sem, 0, key);
    sem_init(&ordering, 0, lock);
    for (int i = 0; i < 5; ++i)
        pthread_create(&man[i], NULL, (void *) use, NULL);
    for (int i = 0; i < 5; ++i)
        pthread_join(man[i], NULL);
    sem_destroy(&ordering);
    sem_destroy(&sem);
    return 0;
}

