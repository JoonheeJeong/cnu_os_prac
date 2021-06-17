#include <stdio.h>
#include <pthread.h>

static volatile int counter = 0;
static const int end = 100000000;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *mythread(void *arg)
{
    printf("%s[%u]: begin\n", (char *) arg, (unsigned) pthread_self());
    pthread_mutex_lock(&lock);
    for (int i = 0; i < end; i++)
        --counter;
    pthread_mutex_unlock(&lock);
    printf("%s[%u]: done\n", (char *) arg, (unsigned) pthread_self());
    return NULL;
}

int main()
{
    printf("main[%u]: begin (counter = %d)\n", (unsigned) pthread_self(), counter);
    pthread_t t1;
    pthread_create(&t1, NULL, mythread, "A");
    pthread_mutex_lock(&lock);
    for (int i = 0; i < end; i++)
        counter++;
    pthread_mutex_unlock(&lock);
    pthread_join(t1, NULL);
    printf("main[%u]: done (counter = %d)\n", (unsigned) pthread_self(), counter);
    return 0;
}

