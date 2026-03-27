#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

void rms(int cap[], int period[], int n) {
    int hyper = period[0];
    for (int i = 1; i < n; i++) {
        hyper = lcm(hyper, period[i]);
    }
    printf("LCM=%d\n\n", hyper);

    printf("---Rate Monotonic Scheduling---\n");
    printf("PID\tcapacity\tPeriod\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", i+1, cap[i], period[i]);
    }

    printf("\nScheduling occurs for %d ms\n\n", hyper);

    int remaining[n];
    for (int i = 0; i < n; i++) remaining[i] = 0;

    int last = -2;

    for (int t = 0; t < hyper; t++) {
        for (int i = 0; i < n; i++) {
            if (t % period[i] == 0) {
                remaining[i] = cap[i];
            }
        }

        int chosen = -1;
        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                if (chosen == -1 || period[i] < period[chosen]) {
                    chosen = i;
                }
            }
        }

        if (chosen != -1) {
            if (chosen != last) {
                printf("%dms onwards: Process %d running\n", t, chosen+1);
                last = chosen;
            }
            remaining[chosen]--;
        } else {
            if (last != -1) {
                printf("%dms onwards: CPU is idle\n", t);
                last = -1;
            }
        }
    }
}
int main() {
    printf("USN: 1BM25CS441\n");
    int n;
    double sum = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int cap[n], period[n];
    printf("Enter capacity,period:\n");
    for (int i = 0; i < n; i++) {
        printf("p[%d] : ", i+1);
        scanf("%d %d", &cap[i], &period[i]);
        sum += (double)cap[i] / period[i];
    }

    if (sum <= 1) {
        rms(cap, period, n);
    } else {
        printf("Not possible\n");
    }
    return 0;
}

