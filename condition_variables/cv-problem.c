#include <stdio.h>
#include <pthread.h>

#define LIMIT 100000 // 10만

int counter = 0;

void work1()
{
    while (counter != LIMIT)
	counter++;
    printf("child: work1 done\n");
}

void *child(void *arg) 
{
    printf("child: begin\n");

    work1();

    printf("child: return\n");
    return 0;
}

int main()
{
    pthread_t t1;

    printf("parent: begin\n");
    pthread_create(&t1, NULL, child, NULL);

    while (counter != LIMIT)
	;
    printf("counter: %d\n", counter);

    printf("parent: return\n");
    return 0;
}
