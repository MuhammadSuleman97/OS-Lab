/* MONTE CARLO (No waiting by parent thread)  */ 

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int size, first = 0, second = 1, third, n;
int arr[100];
int flag=0; 



void *fib(void *arg){
	
	for(int i=0;i<n;i++)
		
	{
		
	  	arr[i] = first;
		third=first+second;
	  	first=second;
	  	second=third;
	}
	flag=1;
	pthread_exit(0);
}


int main(){
	
	pthread_t thread;
	
	printf("Enter Total Number of fib Series:");
	scanf("%d",&n);
	printf("\n");
	pthread_create(&thread,NULL,&fib,NULL);
	
	
	while(1){
		if (flag){
			for (int i=0; i<n; i++){
			printf("%d ",arr[i]);
			}
		break;
		}
	}
	printf("\n");	
}




















