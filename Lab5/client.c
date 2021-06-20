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

void sub(void *param) {
    struct data *temp;
    temp = (struct data*)param;

    printf("I subtract two values %d and %d result = %d\n",temp->a, temp->b, temp->a - temp->b);
}

void mul(void *param) {
    struct data *temp;
    temp = (struct data*)param;

    printf("I multiply two values %d and %d result = %d\n",temp->a, temp->b, temp->a * temp->b);
}

void div(void *param) {
    struct data *temp;
    temp = (struct data*)param;

    printf("I divide two values %d and %d result = %d\n",temp->a, temp->b, temp->a / temp->b);
}

void mod(void *param) {
    struct data *temp;
    temp = (struct data*)param;

    printf("I take modulus of two values %d and %d result = %d\n",temp->a, temp->b, temp->a % temp->b);
}


int main(void)
{
    // create some work to do
    struct data work;

    //addition a+b
    work.a = 10;
    work.b = 5;
    // initialize the thread pool
    pool_init();
    // submit the work to the queue
    pool_submit(&add,&work);

    sleep(2);

    //Subtraction a-b
    pool_submit(&sub,&work);

    sleep(2);

    //Multiply a*b
    pool_submit(&mul,&work);

    sleep(2);

    //Divide a/b
    pool_submit(&div,&work);

    sleep(2);

    // Modulo a%b
    pool_submit(&mod,&work);

    sleep(2);
    pool_shutdown();

    return 0;
}
