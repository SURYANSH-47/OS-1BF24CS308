#include <stdio.h>

int main()
{
    int n, TQ, time = 0, completed = 0;
    int at[20], bt[20], rt[20], ct[20], tat[20], wt[20];
    int queue[100], front = 0, rear = 0;
    int visited[20] = {0}, in_queue[20] = {0};
    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("P%d Arrival & Burst: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &TQ);

    while (completed < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= time && !visited[i])
            {
                queue[rear++] = i;
                visited[i] = 1;
                in_queue[i] = 1;
            }
        }

        if (front == rear)
        {
            time++;
            continue;
        }

        int p = queue[front++];
        in_queue[p] = 0;

        if (rt[p] > TQ)
        {
            time += TQ;
            rt[p] -= TQ;

            for (int i = 0; i < n; i++)
            {
                if (at[i] <= time && !visited[i])
                {
                    queue[rear++] = i;
                    visited[i] = 1;
                    in_queue[i] = 1;
                }
            }
            queue[rear++] = p;
            in_queue[p] = 1;
        }
        else
        {
            time += rt[p];
            rt[p] = 0;
            ct[p] = time;
            completed++;

            for (int i = 0; i < n; i++)
            {
                if (at[i] <= time && !visited[i])
                {
                    queue[rear++] = i;
                    visited[i] = 1;
                    in_queue[i] = 1;
                }
            }
        }
    }

    printf("\nID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        total_tat += tat[i];
        total_wt += wt[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);

    return 0;
}