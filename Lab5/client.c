/*
 * Example client program that uses thread pool.
 */
#include <stdio.h>
#include <unistd.h>
#include "threadpool.h"
#include <math.h>

#define PI 3.14159265

struct data
{
    int a;
    int b;
	int c;
};

void add(void *param)
{
    struct data *temp;

    temp = (struct data*)param;
    printf("I add two values %d and %d result = %d\n",
           temp->a, temp->b, temp->a + temp->b);
}


void sinAngle(void *param){
	struct data *temp;
	temp = (struct data*)param;
	printf("Sin of %d is : %f\n",temp->c,sin(temp->c * PI/180));
	
}

void cosAngle(void *param){
	struct data *temp;
	temp = (struct data*)param;
	printf("Cos of %d is : %f\n",temp->c,cos(temp->c * PI/180));
	
}

void tanAngle(void *param){
	struct data *temp;
	temp = (struct data*)param;
	printf("Tan of %d is : %f\n",temp->c,tan(temp->c * PI/180));
	
}
int main(void)
{

    struct data work;

    // initialize the thread pool
    pool_init();

    // 1st test
    work.a = 5;
    work.b = 10;
	work.c = 30;
	
    pool_submit(add, &work);
	
	//2nd test
	work.c = 30;
	pool_submit(sinAngle, &work);
    
    // wait for free slots in the task queue
    sleep(1);

    // 3rd test
	pool_submit(cosAngle, &work);
	
	//4th test
	pool_submit(tanAngle, &work);

    pool_shutdown();
    return 0;
}

