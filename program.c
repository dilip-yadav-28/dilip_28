#include <stdio.h>

struct process {
    int id, at, bt, ct, tat, wt, rt;
};

int main() {
    int n;
    printf("DILIP.V","1BM25CS441");
    printf("Number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    for(int i = 0; i < n; i++) {
        p[i].id = i + 1;

        printf("Arrival Time of P%d: ", p[i].id);
        scanf("%d", &p[i].at);

        printf("Burst Time of P%d: ", p[i].id);
        scanf("%d", &p[i].bt);
    }


    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(p[j].at > p[j+1].at) {
                struct process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    int timePassed = 0;
    int sumTAT = 0, sumWT = 0, sumRT = 0;

    for(int i = 0; i < n; i++) {

        if(timePassed < p[i].at)
            timePassed = p[i].at;

        p[i].rt = timePassed - p[i].at;

        p[i].ct = timePassed + p[i].bt;

        p[i].tat = p[i].ct - p[i].at;

        p[i].wt = p[i].tat - p[i].bt;

        timePassed += p[i].bt;

        sumTAT += p[i].tat;
        sumWT += p[i].wt;
        sumRT += p[i].rt;
    }

    printf("\nAverage TAT: %.2f\n", (float)sumTAT/n);
    printf("Average WT: %.2f\n", (float)sumWT/n);
    printf("Average RT: %.2f\n", (float)sumRT/n);

    return 0;
}
