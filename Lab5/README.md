These files support the POSIX implementation of the thread pool project.

Source files:

- client.c (client program that uses thread pool)

- threadpool.c (implementation of thread pool)

- threadpool.h (header file containing function prototypes)

Client file has 4 test functions which are implemented by thread polling
    1- Addition  of two numbers
    2- Sin of a number
    3- Cos of a number
    4- Tan ofa number

To run the Program use these commands

1---  gcc threadpool.c -c -lpthread
2---  gcc threadpool.o client.c -o threadpool -lpthread -lm
3--- ./threadpool

