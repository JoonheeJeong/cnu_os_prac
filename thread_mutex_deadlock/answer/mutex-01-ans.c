#include <stdio.h>
#include <pthread.h>

const int THREAD_COUNT = 3;
volatile int counter = 0;
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *print_twice(void *arg)
{
    char *name = (char *) arg;
    pthread_mutex_lock(&counter_mutex);
    counter++;
    printf("[%s started] counter: %d\n", name, counter);
    for(int i = 0; i < 100000; ++i)
	;
    printf("[%s finished] counter: %d\n", name, counter);
    pthread_mutex_unlock(&counter_mutex);
    return NULL;
}

int main()
{
    pthread_t thread[THREAD_COUNT];
    char thread_name[THREAD_COUNT][16];

    for (int i = 0; i < THREAD_COUNT; ++i) {
	sprintf(thread_name[i], "thread_%d", i+1);
        pthread_create(&thread[i], NULL, &print_twice, thread_name[i]);
    }

    for (int i = 0; i < THREAD_COUNT; ++i)
	pthread_join(thread[i], NULL);

    return 0;
}
