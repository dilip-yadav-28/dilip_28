#include <stdio.h>

int main()
{
    int n, i, j;
    int pid[20], at[20], bt[20], pr[20];
    int ct[20], tat[20], wt[20];
    int completed[20] = {0};

    int current_time = 0, completed_count = 0;
    int highest_priority, selected;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        printf("\nProcess %d ID: ",i+1);
        scanf("%d",&pid[i]);

        printf("Arrival Time: ");
        scanf("%d",&at[i]);

        printf("Burst Time: ");
        scanf("%d",&bt[i]);

        printf("Priority: ");
        scanf("%d",&pr[i]);
    }

    while(completed_count < n)
    {
        highest_priority = 9999;
        selected = -1;

        for(i=0;i<n;i++)
        {
            if(at[i] <= current_time && completed[i] == 0)
            {
                if(pr[i] < highest_priority)
                {
                    highest_priority = pr[i];
                    selected = i;
                }
            }
        }

        if(selected == -1)
        {
            current_time++;
        }
        else
        {
            ct[selected] = current_time + bt[selected];
            tat[selected] = ct[selected] - at[selected];
            wt[selected] = tat[selected] - bt[selected];

            current_time = ct[selected];
            completed[selected] = 1;
            completed_count++;
        }
    }

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for(i=0;i<n;i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        pid[i],at[i],bt[i],pr[i],ct[i],tat[i],wt[i]);
    }

    return 0;
}
