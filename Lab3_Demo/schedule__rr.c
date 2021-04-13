#include<stdio.h>
 
int main()
{
      int i, limit, total = 0, x, counter = 0, q;
      int wt = 0, tat = 0, arr_time[10], bt[10], temp[10];
      float avg_wt, avg_tat;
      printf("\nEnter Total Number of Processes:\t");
      scanf("%d", &limit);	//taking user input
      x = limit;
      for(i = 0; i < limit; i++)
      {
            printf("\nEnter Details of Process[%d]\n", i + 1);
 
            printf("Arrival Time:\t");
 
            scanf("%d", &arr_time[i]);
 
            printf("\nBurst Time:\t");
 
            scanf("%d", &bt[i]);
 
            temp[i] = bt[i];
      }
 
      printf("\nEnter Time Quantum:\t");
      scanf("%d", &q); // taking quantum from user
      printf("\nProcess ID\t\tBurst Time\t Turnaround Time\t Waiting Time\n");
      for(total = 0, i = 0; x != 0;)
      {
            if(temp[i] <= q && temp[i] > 0)
            {
                  total = total + temp[i];
                  temp[i] = 0;
                  counter = 1;
            }
            else if(temp[i] > 0)
            {
                  temp[i] = temp[i] - q;
                  total = total + q;
            }
            if(temp[i] == 0 && counter == 1)
            {
                  x--;
                  printf("\nProcess[%d]\t\t%d\t\t %d\t\t\t %d", i + 1, bt[i], total - arr_time[i], total - arr_time[i] - bt[i]);
                  wt = wt + total - arr_time[i] - bt[i];
                  tat = tat + total - arr_time[i];
                  counter = 0;
            }
            if(i == limit - 1)
            {
                  i = 0;
            }
            else if(arr_time[i + 1] <= total)
            {
                  i++;
            }
            else
            {
                  i = 0;
            }
      }
 
      avg_wt = wt * 1.0 / limit;
      avg_tat = tat * 1.0 / limit;
      printf("\n\nAverage Waiting Time:\t%f", avg_wt);
      printf("\nAvg Turnaround Time:\t%f\n", avg_tat);
      return 0;
}