#include <stdio.h>
#include <stdlib.h> // malloc, free
#include <pthread.h>

typedef struct { int a; int b; } myarg_t;
typedef struct { int mul; } myret_t;

void *mythread(void *arg) {
    myarg_t *args = (myarg_t *) arg;
    printf("args %d %d\n", args->a, args->b);
    myret_t *rvals = malloc(sizeof(myret_t));
    rvals->mul = args->a * args->b;
    return (void *) rvals;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    myret_t *rvals; // 쓰레드 데이터 저장을 위한 포인터 (12,24번줄 참고)
    myarg_t args = { 10, 20 };
    pthread_create(&p, NULL, mythread, &args);
    pthread_join(p, (void **) &rvals);
    printf("returned %d\n", rvals->mul);
    free(rvals);
    return 0;
}

