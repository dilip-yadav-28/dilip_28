#include <stdio.h>

struct Process {
    int pid, at, bt, rt, ct, wt, tat;
};

// Sorts processes by Arrival Time (AT)
void sortArrival(struct Process p[], int n) {
    struct Process temp;
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            if(p[j].at > p[j+1].at) {
                temp = p[j]; p[j] = p[j+1]; p[j+1] = temp;
            }
        }
    }
}

int main() {
    int n, quantum, completed = 0, curr_time = 0;
    float total_wt = 0, total_tat = 0;
    int queue[100], front = 0, rear = 0;
    int mark[100] = {0}; // Tracks if a process is already in the queue

    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];

    for(int i=0; i<n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt; // Remaining time starts as burst time
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    sortArrival(p, n);

    // Start with the first process that arrives
    curr_time = p[0].at;
    queue[rear++] = 0;
    mark[0] = 1;

    while(completed != n) {
        int idx = queue[front++]; // Dequeue

        // Execute for quantum or remaining time, whichever is smaller
        int slice = (p[idx].rt > quantum) ? quantum : p[idx].rt;
        p[idx].rt -= slice;
        curr_time += slice;

        // 1. Check for processes that arrived while current process was running
        for(int i = 0; i < n; i++) {
            if(p[i].at <= curr_time && mark[i] == 0 && p[i].rt > 0) {
                queue[rear++] = i;
                mark[i] = 1;
            }
        }

        // 2. If current process is not finished, put it back at the end of queue
        if(p[idx].rt > 0) {
            queue[rear++] = idx;
        } else {
            // Process finished
            p[idx].ct = curr_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            total_wt += p[idx].wt;
            total_tat += p[idx].tat;
            completed++;
        }

        // 3. Handle CPU Idle time (if queue is empty but processes remain)
        if(front == rear && completed < n) {
            for(int i = 0; i < n; i++) {
                if(mark[i] == 0) {
                    curr_time = p[i].at;
                    queue[rear++] = i;
                    mark[i] = 1;
                    break;
                }
            }
        }
    }

    // Output Table
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    printf("--------------------------------------------------\n");
    for(int i=0; i<n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
