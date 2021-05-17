#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>


int i = 0,num = 0, PointsInCircle  = 0;

pthread_mutex_t lock;


void *count(void *arg)
{ 
    pthread_mutex_lock(&lock);
   
    for (int i=0; i < num; i++)
    {	
        double X = (double)rand() / RAND_MAX;
        double Y = (double)rand() / RAND_MAX;
        
        if (((X * X) + (Y * Y)) <= 1)
        {
            PointsInCircle++;
        }
    }
    
    pthread_mutex_unlock(&lock);
    pthread_exit(0);
}

int main()
{
    
    pthread_t thread;
    
    printf("Enter a positive number of points: ");
    scanf("%d", &num); 
  
    pthread_create(&thread, NULL, &count, NULL);
    pthread_join(thread, NULL);
    
    double pi = (4.0 * PointsInCircle) / num;
    printf("The approximate value of Pi for points (%d) is: %f \n", num, pi);  
    
    pthread_mutex_destroy(&lock);
}




