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

void *routine(void *arg) {
    printf("routine: begin\n");
    printf("routine: state is %d\n", thd->state);
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
    myWaitThread(thd);
    printf("ordering: end\n");
    return 0;
}

