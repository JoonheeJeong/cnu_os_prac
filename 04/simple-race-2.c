#include <stdio.h>
#include <pthread.h>

static volatile int counter = 0; // shared, possible to race
static const int end = 100000000; // shared, but impossible to race (constant)

typedef struct { char *id; int val; } myarg;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *mythread(void *arg)
{
	myarg *ma = (myarg *) arg;
	printf("%s[%u]: begin\n", ma->id, (unsigned) pthread_self());
	/* You may have to wait for about 30 seconds.  */
	/* locking & unlocking is time-consuming work. */
	for (int i = 0; i < end; i++) {
		pthread_mutex_lock(&mutex);
		--counter; // critical section
		pthread_mutex_unlock(&mutex);
		ma->val++; // shared, but don't have to be worry about race
	}
	printf("%s[%u]: done\n", ma->id, (unsigned) pthread_self());
	return (void *) ma;
}

int main()
{
	printf("main[%u]: begin (counter = %d)\n", (unsigned) pthread_self(), counter);
	pthread_t t1, t2;
	myarg ma1 = {"A", end };
	myarg ma2 = {"B", end };
	pthread_create(&t1, NULL, mythread, &ma1);
	pthread_create(&t2, NULL, mythread, &ma2);
	for (int i = 0; i < end; i++) {
		pthread_mutex_lock(&mutex);
		counter++; // critical section
		pthread_mutex_unlock(&mutex);
	}
	pthread_join(t1, (void **) &ma1);
	pthread_join(t2, (void **) &ma2);
	printf("main[%u]: done (counter = %d) (ma1.val = %d) (ma2.val = %d)\n", 
			(unsigned) pthread_self(), counter, ma1.val, ma2.val);
	return 0;
}

