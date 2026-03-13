#include <stdio.h>

int main()
{
    int n,i;
    int pid[20],at[20],bt[20],pr[20];
    int ct[20],tat[20],wt[20];
    int completed[20]={0};

    int current_time=0,count=0;
    int highest_priority,selected;

    int sum_tat=0,sum_wt=0;
    float avg_tat,avg_wt;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        printf("\nProcess ID: ");
        scanf("%d",&pid[i]);

        printf("Arrival Time: ");
        scanf("%d",&at[i]);

        printf("Burst Time: ");
        scanf("%d",&bt[i]);

        printf("Priority: ");
        scanf("%d",&pr[i]);
    }

    while(count<n)
    {
        highest_priority=9999;
        selected=-1;

        for(i=0;i<n;i++)
        {
            if(at[i]<=current_time && completed[i]==0)
            {
                if(pr[i]<highest_priority)
                {
                    highest_priority=pr[i];
                    selected=i;
                }
            }
        }

        if(selected==-1)
        {
            current_time++;
        }
        else
        {
            current_time += bt[selected];

            ct[selected]=current_time;
            tat[selected]=ct[selected]-at[selected];
            wt[selected]=tat[selected]-bt[selected];

            completed[selected]=1;
            count++;
        }
    }

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for(i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        pid[i],at[i],bt[i],pr[i],ct[i],tat[i],wt[i]);

        sum_tat += tat[i];
        sum_wt += wt[i];
    }

    avg_tat = (float)sum_tat/n;
    avg_wt = (float)sum_wt/n;

    printf("\nAverage Turnaround Time = %.2f",avg_tat);
    printf("\nAverage Waiting Time = %.2f",avg_wt);

    return 0;
}
