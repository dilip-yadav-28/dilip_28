#include<stdio.h>
#include<stdlib.h>

void mlq_scheduling(int at[], int bt[], int q_no[], int n, int tq) {
    int rt[n], ct[n], tat[n], wt[n], completed[n];
    int time = 0, count = 0, last_q1 = -1;
    float avg_tat = 0, avg_wt = 0;

    for(int i = 0; i < n; i++) {
        rt[i] = bt[i];
        completed[i] = 0;
    }

    while(count < n) {
        int idx = -1;

        //Queue 1-Round Robin
        for(int i = 1; i <= n; i++) {
            int j = (last_q1 + i) % n;
            if(q_no[j] == 1 && at[j] <= time && completed[j] == 0) {
                idx = j;
                break;
            }
        }

        if(idx != -1) {
            int slice = (rt[idx] > tq) ? tq : rt[idx];
            time += slice;
            rt[idx] -= slice;
            last_q1 = idx;

            if(rt[idx] == 0) {
                ct[idx] = time;
                completed[idx] = 1;
                count++;
            }
        }
        else {
            //Queue 2-FCFS
            for(int i = 0; i < n; i++) {
                if(q_no[i] == 2 && at[i] <= time && completed[i] == 0) {
                    idx = i;
                    break;
                }
            }

            if(idx != -1) {
                rt[idx]--;
                time++;
                if(rt[idx] == 0) {
                    ct[idx] = time;
                    completed[idx] = 1;
                    count++;
                }
            } else {
                time++;
            }
        }
    }

    printf("\nPID\tQ_No\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i+1, q_no[i], at[i], bt[i], ct[i], tat[i], wt[i]);
        avg_tat += tat[i];
        avg_wt += wt[i];
    }
    printf("\nAvg TAT: %.2f", avg_tat/n);
    printf("\nAvg WT: %.2f\n", avg_wt/n);
}

int main() {
    printf("USN:1BM25CS441\n");
    int n, tq = 2;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], q_no[n];
    printf("Enter the Queue_No, AT and BT\n");
    for(int i = 0; i < n; i++) {
        printf("p[%d] : ", i+1);
        scanf("%d %d %d", &q_no[i], &at[i], &bt[i]);
    }

    mlq_scheduling(at, bt, q_no, n, tq);

    return 0;
}
