#include <stdio.h>

#define MAX 20

struct Process {
    int id, at, bt, ct, tat, wt, type, completed;
};

int main() {
    int n, time = 0, completedCount = 0;
    struct Process p[MAX];

    printf("Enter total number of processes: ");
    scanf("%d", &n);

    // Input
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;

        printf("\nProcess %d\n", p[i].id);

        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Enter Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Enter Process Type (1=System, 2=User): ");
        scanf("%d", &p[i].type);

        p[i].completed = 0;
    }

    // Scheduling
    while (completedCount < n) {
        int idx = -1;
        int min_at = 1e9;

        // Priority: System processes first
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= time) {

                // System queue priority
                if (p[i].type == 1) {
                    if (p[i].at < min_at) {
                        min_at = p[i].at;
                        idx = i;
                    }
                }
            }
        }

        // If no system process, take user process
        if (idx == -1) {
            min_at = 1e9;
            for (int i = 0; i < n; i++) {
                if (!p[i].completed && p[i].at <= time && p[i].type == 2) {
                    if (p[i].at < min_at) {
                        min_at = p[i].at;
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            time += p[idx].bt;

            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            p[idx].completed = 1;
            completedCount++;
        } else {
            time++;
        }
    }

    // Output
    float total_tat = 0, total_wt = 0;

    printf("\n--- Scheduling Results ---\n");
    printf("PID\tType\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id,
               (p[i].type == 1) ? "SYS" : "USR",
               p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);

        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }

    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);

    return 0;
}
