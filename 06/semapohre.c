#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAN 5
int key = 4;
sem_t sem;

void use();

int main()
{
    pthread_t man[MAN];

    sem_init(&sem, 0, key);
    for (int i = 0; i < 5; ++i)
        pthread_create(&man[i], NULL, (void *) use, NULL);
    for (int i = 0; i < 5; ++i)
        pthread_join(man[i], NULL);
    sem_destroy(&sem);
    return 0;
}

void use()
{
    sem_wait(&sem);
    key--;
    printf("%u In (key:%d)\n", (unsigned) pthread_self(), key);
    usleep(100);
    key++;
    sem_post(&sem);
    printf("%u Out (key:%d)\n", (unsigned) pthread_self(), key);
}
