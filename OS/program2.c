#include <stdio.h>

struct process {
    int id, at, bt, ct, tat, wt, rt;
};

int main() {

    int n;
    printf( "DILIP.V 1BM25CS441\n");
    printf("Enter no. of processes: ");
    scanf("%d", &n);

    struct process p[n];

    for(int i = 0; i < n; i++) {
        p[i].id = i + 1;

        printf("Arrival Time of P%d: ", p[i].id);
        scanf("%d", &p[i].at);

        printf("Burst Time of P%d: ", p[i].id);
        scanf("%d", &p[i].bt);
    }

    int completed = 0, time = 0;
    int sumTAT = 0, sumWT = 0;

    int isComplete[n];

    for(int i = 0; i < n; i++)
        isComplete[i] = 0;

    while(completed != n) {

        int idx = -1;
        int minBT = 9999;

        for(int i = 0; i < n; i++) {

            if(p[i].at <= time && !isComplete[i]) {

                if(p[i].bt < minBT) {
                    minBT = p[i].bt;
                    idx = i;
                }
            }
        }

        if(idx != -1) {

            p[idx].ct = time + p[idx].bt;

            p[idx].tat = p[idx].ct - p[idx].at;

            p[idx].wt = p[idx].tat - p[idx].bt;

            sumTAT += p[idx].tat;
            sumWT += p[idx].wt;

            time += p[idx].bt;

            isComplete[idx] = 1;

            completed++;
        }
        else {
            time++;
        }
    }

    printf("\nAverage TAT: %.2f\n", (float)sumTAT/n);
    printf("Average WT: %.2f\n", (float)sumWT/n);

    return 0;
}



