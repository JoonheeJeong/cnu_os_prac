#include <assert.h>
#include <stdio.h>
#include <pthread.h>

typedef struct {
    int a;
    int b;
} myarg_t;

void *mythread(void *arg) { // void 포인터는 아무 포인터나 받을 수 있음
    myarg_t *args = (myarg_t *) arg;
    printf("%d %d\n", args->a, args->b);
    return NULL; // 쓰레드 종료 후 따로 저장할 값 없으면 Null
}

int main(int argc, char *argv[]) {
    pthread_t p;
    myarg_t args = { 10, 20 };

    int rc = pthread_create(&p, NULL, mythread, &args); // 별도의 쓰레드 설정 없으므로 Null
    assert(rc == 0); // rc가 0이 아니면 프로그램 종료  (thread 생성 에러)
    pthread_join(p, NULL); // 종료상태 필요 없으므로 Null
    printf("done\n");
    return 0;
}
