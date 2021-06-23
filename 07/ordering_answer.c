#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define STATE_INIT (0)

typedef struct {
    pthread_t th;
    int state;
} my_thread_t;

my_thread_t *thd;
int chk = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void *routine(void *arg) {
    printf("routine: begin\n");

    pthread_mutex_lock(&m);
    while (chk == 0)
        pthread_cond_wait(&c, &m);
    printf("routine: state is %d\n", thd->state);
    pthread_mutex_unlock(&m);
    return NULL;
}

void myWaitThread(my_thread_t *p) {
    pthread_join(p->th, NULL); 
}

my_thread_t *myCreateThread(void *(*start_routine)(void *)) {
    my_thread_t *p = malloc(sizeof(my_thread_t));
    if (p == NULL) 
	    return NULL;
    p->state = STATE_INIT;
    pthread_create(&p->th, NULL, start_routine, NULL); 
    // turn the sleep off to avoid the fault, sometimes...
    sleep(1);
    return p;
}

int main(int argc, char *argv[]) {
    printf("ordering: begin\n");
    thd = myCreateThread(routine);

    pthread_mutex_lock(&m);
    chk = 1;
    pthread_cond_signal(&c);
    pthread_mutex_unlock(&m);

    myWaitThread(thd);
    printf("ordering: end\n");
    return 0;
}

