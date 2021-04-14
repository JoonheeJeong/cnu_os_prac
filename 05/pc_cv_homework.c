#include <stdio.h>
#include <pthread.h>
#include <unistd.h>     // usleep (micro sleep)

#define MAX 10 
#define PROD_SIZE 3
#define CONS_SIZE 7
#define PROD_ITEM 5
#define CONS_ITEM 2

/* homework */
/*----------*/
/* You need to make some variables (mutex, condition variables). */
/* Reference below variables, functions. */
/*----------*/
/* homework */

pthread_mutex_t m_id = PTHREAD_MUTEX_INITIALIZER;
int buffer[MAX]; // ! buffer is circular queue !
int count = 0;
int get_ptr = 0;
int put_ptr = 0;
int prod_id = 1;
int cons_id = 1;

/* homework */
// return buffer's value using get_ptr if successful,
// otherwise, -1
int get()
{
    return -1;
}

/* homework */
// return buffer's value using put_ptr if successful,
// otherwise, -1
int put(int val)
{
    return -1;
}

void *producer(void *arg)
{
    pthread_mutex_lock(&m_id);
    int id = prod_id++;
    pthread_mutex_unlock(&m_id);
    for (int i = 0; i < PROD_ITEM; ++i) {
        usleep(10);

        /* homework */
        /*----------*/
        int ret = put(i);
        /*----------*/
        /* homework */

        if (ret == -1) {
            printf("can't put, becuase buffer is full.\n");
        } else {
            printf("producer %d PUT %d\n", id, ret);
        }
    }
}

void *consumer(void *arg)
{
    pthread_mutex_lock(&m_id);
    int id = cons_id++;
    pthread_mutex_unlock(&m_id);
    for (int i = 0; i < CONS_ITEM; ++i) {
        usleep(10);

        /* homework */
        /*----------*/
        int ret = get();
        /*----------*/
        /* homework */

        if (ret == -1) {
            printf("can't get, becuase buffer is empty.\n");
        } else {
            printf("consumer %d GET %d\n", id, ret);
        }
    }
}

int main()
{
    pthread_t prod[PROD_SIZE];
    pthread_t cons[CONS_SIZE];

    for (int i = 0; i < PROD_SIZE; ++i)
        pthread_create(&prod[i], NULL, producer, NULL);
    for (int i = 0; i < CONS_SIZE; ++i)
        pthread_create(&cons[i], NULL, consumer, NULL);

    for (int i = 0; i < PROD_SIZE; ++i)
        pthread_join(prod[i], NULL);
    for (int i = 0; i < CONS_SIZE; ++i)
        pthread_join(cons[i], NULL);

    return 0;
}
