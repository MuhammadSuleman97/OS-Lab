#include<stdio.h> 
void TurnAroundTime( int processes[], int n, int bt[], int wt[], int tat[]) 

{ 

    for (int  i = 0; i < n ; i++) 

        tat[i] = bt[i] + wt[i]; 

} 
void WaitingTime(int processes[], int n,int bt[], int wt[]) 
{ 
    wt[0] = 0; 
    for (int  i = 1; i < n ; i++ ) 
        wt[i] =  bt[i-1] + wt[i-1] ; 
} 


void AvgTime( int processes[], int n, int bt[]) 
{ 
    int WT[n], TAT[n], T_WT = 0, T_TAT = 0; 

    WaitingTime(processes, n, bt, WT); 

    TurnAroundTime(processes, n, bt, WT, TAT); 


    printf("Processes\tBurst time\tWaiting time\tTurn around time\n"); 

    for (int  i=0; i<n; i++) 

    { 
        T_WT = T_WT + WT[i]; 
        T_TAT = T_TAT + TAT[i]; 
        printf("%d ",(i+1));
        printf("\t\t%d ", bt[i] );
        printf("\t\t%d",WT[i] );
        printf("\t\t%d\n",TAT[i] ); 
    } 
    int s=(float)T_WT / (float)n;
    int t=(float)T_TAT / (float)n;
    printf("Average waiting time = %d",s);
    printf("\n");
    printf("Average turn around time = %d \n",t); 
} 


int main() 
{ 

    int Processes[] = { 1, 2, 3, 4, 5, 6}; 
    int n = sizeof Processes / sizeof Processes[0]; 
    int  Burst_Time[] = {50,50,50,50,50,50}; 
    AvgTime(Processes, n,  Burst_Time); 
	return 0; 
}

