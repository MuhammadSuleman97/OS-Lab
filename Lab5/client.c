/**
 * Example client program that uses thread pool.
 */

#include <stdio.h>
#include <unistd.h>
#include "threadpool.h"
#include <time.h>
struct data
{
    int a;
    int b;
};

void add(void *param) {
    struct data *temp;
    temp = (struct data*)param;

    printf("I add two values %d and %d result = %d\n",temp->a, temp->b, temp->a + temp->b);
}

int main(void)
{
    // create some work to do
    struct data work;
    work.a = 5;
    work.b = 10;

    // initialize the thread pool
    pool_init();
    // submit the work to the queue
    pool_submit(&add,&work);

    sleep(2);
    work.a = 10;
    work.b = 10;
    pool_submit(&add,&work);
    sleep(2);
    work.a = 15;
    work.b = 10;
    pool_submit(&add,&work);

    sleep(2);
    work.a = 5;
    work.b = 20;
    pool_submit(&add,&work);
    sleep(2);

    work.a = 30;
    work.b = 10;
    pool_submit(&add,&work);

    sleep(2);
    work.a = 50;
    work.b = 10;
    pool_submit(&add,&work);

    sleep(2);
    pool_shutdown();

    return 0;
}
