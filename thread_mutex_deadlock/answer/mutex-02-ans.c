#include <stdio.h>
#include <pthread.h>

const int end = 100000000; // shared, but impossible to race (constant)
volatile int counter = 0; // shared, possible to race

typedef struct { char *id; int val; } myarg;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* Here, real critical section is only '--counter' line in the for loop.
   However, locking-unlocking is time-consuming work.
   Therefore, if you wrap around only the '--counter' line tightly
   (22 lock, 24 unlock),
   the waiting time will be about 30 secs!
   So, it's good to put locking-unlocking codes outside the for loop.*/
void *mythread(void *arg)
{
    myarg *ma = (myarg *) arg;
    printf("%s[%u]: begin\n", ma->id, (unsigned) pthread_self());
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < end; i++) {
	--counter; // critical section
	ma->val++; // shared, but don't have to be worry about race
    }
    pthread_mutex_unlock(&mutex);
    printf("%s[%u]: done\n", ma->id, (unsigned) pthread_self());
    return (void *) ma;
}

int main()
{
    printf("main[%u]: begin (counter = %d)\n", (unsigned) pthread_self(), counter);
    pthread_t t1;
    myarg ma1 = {"A", end };
    pthread_create(&t1, NULL, mythread, &ma1);
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < end; i++)
	counter++; // critical section
    pthread_mutex_unlock(&mutex);
    pthread_join(t1, (void **) &ma1);
    printf("main[%u]: done (counter = %d) (ma1.val = %d)\n", 
	(unsigned) pthread_self(), counter, ma1.val);
    return 0;
}

