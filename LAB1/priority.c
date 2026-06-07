#include <stdio.h>

void nonPreemptivePriority(int n, int at_in[], int bt_in[], int pr_in[], int p_in[])
{
    int at[20], bt[20], pr[20], p[20], wt[20], tat[20], ct[20], completed[20] = {0};
    int count = 0, current_time = 0;
    float twt = 0, ttat = 0;

    for (int i = 0; i < n; i++)
    {
        at[i] = at_in[i];
        bt[i] = bt_in[i];
        pr[i] = pr_in[i];
        p[i] = p_in[i];
    }

    while (count < n)
    {
        int idx = -1;
        int max_priority = 1e9;

        for (int i = 0; i < n; i++)
        {
            if (at[i] <= current_time && !completed[i])
            {
                if (pr[i] < max_priority)
                {
                    max_priority = pr[i];
                    idx = i;
                }
            }
        }

        if (idx == -1)
        {
            current_time++;
        }
        else
        {
            ct[idx] = current_time + bt[idx];
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            current_time = ct[idx];
            completed[idx] = 1;
            count++;
            twt += wt[idx];
            ttat += tat[idx];
        }
    }

    printf("\n==============================================");
    printf("\n         NON-PREEMPTIVE PRIORITY");
    printf("\n==============================================");
    printf("\nID\tPR\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i], pr[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    printf("\nAverage Waiting Time: %.2f", twt / n);
    printf("\nAverage Turnaround Time: %.2f\n", ttat / n);
}

void preemptivePriority(int n, int at_in[], int bt_in[], int pr_in[], int p_in[])
{
    int rt[20], wt[20], tat[20], ct[20];
    int count = 0, t = 0, min_pr = 1e9, highest = -1;
    float twt = 0, ttat = 0;

    for (int i = 0; i < n; i++)
        rt[i] = bt_in[i];

    while (count < n)
    {
        highest = -1;
        min_pr = 1e9;

        for (int j = 0; j < n; j++)
        {
            if (at_in[j] <= t && rt[j] > 0)
            {
                if (pr_in[j] < min_pr)
                {
                    min_pr = pr_in[j];
                    highest = j;
                }
            }
        }

        if (highest == -1)
        {
            t++;
            continue;
        }

        rt[highest]--;

        if (rt[highest] == 0)
        {
            count++;
            ct[highest] = t + 1;
            wt[highest] = ct[highest] - bt_in[highest] - at_in[highest];
            if (wt[highest] < 0)
                wt[highest] = 0;
        }
        t++;
    }

    printf("\n==============================================");
    printf("\n           PREEMPTIVE PRIORITY");
    printf("\n==============================================");
    printf("\nID\tPR\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        tat[i] = bt_in[i] + wt[i];
        twt += wt[i];
        ttat += tat[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p_in[i], pr_in[i], at_in[i], bt_in[i], ct[i], tat[i], wt[i]);
    }
    printf("\nAverage Waiting Time: %.2f", twt / n);
    printf("\nAverage Turnaround Time: %.2f\n", ttat / n);
}

int main()
{
    int n, at[20], bt[20], pr[20], p[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        p[i] = i + 1;
        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        printf("P%d Priority (Lower is higher): ", i + 1);
        scanf("%d", &pr[i]);
    }

    nonPreemptivePriority(n, at, bt, pr, p);
    preemptivePriority(n, at, bt, pr, p);

    return 0;
}