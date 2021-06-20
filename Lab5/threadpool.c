/**
 * Implementation of thread pool.
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include "threadpool.h"

#define NUMBER_OF_THREADS 3
void execute(void (*somefunction)(void *p), void *p);

// Global Variables
queue* Q;
pthread_t bee[NUMBER_OF_THREADS];
sem_t queue_check;

int shutdown = 0;
// initializing the Queue
void q_init(void) {
    Q = malloc(sizeof(queue));
    Q -> Front = Q -> Rear = malloc(sizeof(node));
    Q -> Rear -> Next = NULL;
}

// returns 0 if successful or 1 otherwise,
int enqueue(task t) {
    node* tmp = malloc(sizeof(node));
    Q->Rear->T = t;
    Q->Rear->Next = tmp;
    Q->Rear = tmp;
    tmp->Next = NULL;
    sem_post(&queue_check);
    return 0;
}

// remove a task from the queue
task dequeue() {
    node* tmp = Q -> Front;
    task worktodo = tmp -> T;

    Q -> Front = Q -> Front -> Next;
    free(tmp);

    return worktodo;
}

// the worker thread in the thread pool
void *worker(void *param) {
    task worktodo;
    while(1){
        sem_wait(&queue_check);
        if(shutdown) break;
        worktodo = dequeue();
        execute(worktodo.function, worktodo.data);
    }
    sem_post(&queue_check);
    pthread_exit(0);
}

/**
 * Executes the task provided to the thread pool
 */
void execute(void (*somefunction)(void *p), void *p) {
    (*somefunction)(p);
}


/**
 * Submits work to the pool.
 */
int pool_submit(void (*somefunction)(void *p), void *p) {
    task worktodo;

    worktodo.function = somefunction;
    worktodo.data = p;

    enqueue(worktodo);
    return 0;
}

// initialize the thread pool
void pool_init(void) {
    int i = 0;
    q_init();
    sem_init(&queue_check, 0, 0);

    for(i = 0; i < NUMBER_OF_THREADS; i++)
        pthread_create(&bee[i],NULL,worker,NULL);
}

// shutdown the thread pool
void pool_shutdown(void) {
    int i;
    shutdown = 1;
    sem_post(&queue_check);

    for(i = 0; i < NUMBER_OF_THREADS; i++)
        pthread_join(bee[i],0);
}
