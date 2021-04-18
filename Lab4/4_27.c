
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int size, first = 0, second = 1, third, n;
int arr[100];

void *fib(void *arg){
	
	for(int i=0;i<n;i++)
		
	{
		
	  	arr[i] = first;
		third=first+second;
	  	first=second;
	  	second=third;
	}
}


int main(){
	
	pthread_t thread;
	
	printf("Enter Total Number of fib Series:");
	scanf("%d",&n);
	printf("\n");
	pthread_create(&thread,NULL,&fib,NULL);
	pthread_join(thread, NULL);
	
	for (int i=0;i<n;i++){
		printf("%d ",arr[i]);
	}
	
}
