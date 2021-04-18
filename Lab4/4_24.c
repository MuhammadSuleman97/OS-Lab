#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

int i         = 0,num = 0, PointsInCircle  = 0;

void *count(void *arg)
{ 
    for (i=0; i < num; i++)
    {	
        double X = (double)rand() / RAND_MAX;
        double Y = (double)rand() / RAND_MAX;
        
        if (((X * X) + (Y * Y)) <= 1)
        {
            PointsInCircle++;
        }
    }
    return NULL;
}

int main()
{
   
    pthread_t thread;
	
	printf("Enter a positive number of points: \n");
    scanf("%d", &num); 
  
    pthread_create(&thread, NULL, &count, NULL);
    pthread_join(thread, NULL);
    
    double pi = (4.0 * PointsInCircle) / num;
    printf("The approximate value of Pi for points (%d) is: %f \n", num, pi);  
    return 0;
}
