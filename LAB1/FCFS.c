#include <stdio.h>

void sort(int n, int at[], int bt[], int p[]) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                temp = at[j]; at[j] = at[j + 1]; at[j + 1] = temp;
                temp = bt[j]; bt[j] = bt[j + 1]; bt[j + 1] = temp;
                temp = p[j]; p[j] = p[j + 1]; p[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, bt[20], wt[20], tat[20], at[20], ct[20], p[20];
    float twt = 0, ttat = 0;

    printf("Enter the number of processes: ");
    if (scanf("%d", &n) != 1) return 1;

    for (int i = 0; i < n; i++) {
        p[i] = i + 1;
        printf("Enter Arrival Time for Process %d: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    sort(n, at, bt, p);

    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < at[i]) {
            current_time = at[i];
        }
        ct[i] = current_time + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        current_time = ct[i];
        
        twt += wt[i];
        ttat += tat[i];
    }

    printf("\nPROCESS\tAT\tBT\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", twt / n);
    printf("\nAverage Turnaround Time = %.2f\n", ttat / n);

    return 0;
}