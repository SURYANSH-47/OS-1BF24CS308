#include <stdio.h>

void nonPreemptiveSJF(int n, int at_in[], int bt_in[], int p_in[])
{
    int at[20], bt[20], p[20], wt[20], tat[20], ct[20], completed[20] = {0};
    int count = 0, current_time = 0;
    float twt = 0, ttat = 0;

    for (int i = 0; i < n; i++)
    {
        at[i] = at_in[i];
        bt[i] = bt_in[i];
        p[i] = p_in[i];
    }

    while (count < n)
    {
        int idx = -1;
        int min_bt = 1e9;

        for (int i = 0; i < n; i++)
        {
            if (at[i] <= current_time && !completed[i])
            {
                if (bt[i] < min_bt)
                {
                    min_bt = bt[i];
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
    printf("\n           NON-PREEMPTIVE SJF");
    printf("\n==============================================");
    printf("\nID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    printf("\nAverage Waiting Time: %.2f", twt / n);
    printf("\nAverage Turnaround Time: %.2f\n", ttat / n);
}

void preemptiveSJF(int n, int at_in[], int bt_in[], int p_in[])
{
    int rt[20], wt[20], tat[20], ct[20];
    int count = 0, t = 0, min_rt = 1e9, shortest = 0, found = 0;
    float twt = 0, ttat = 0;

    for (int i = 0; i < n; i++)
        rt[i] = bt_in[i];

    while (count < n)
    {
        for (int j = 0; j < n; j++)
        {
            if ((at_in[j] <= t) && (rt[j] < min_rt) && rt[j] > 0)
            {
                min_rt = rt[j];
                shortest = j;
                found = 1;
            }
        }

        if (!found)
        {
            t++;
            continue;
        }

        rt[shortest]--;
        min_rt = rt[shortest];
        if (min_rt == 0)
            min_rt = 1e9;

        if (rt[shortest] == 0)
        {
            count++;
            found = 0;
            ct[shortest] = t + 1;
            wt[shortest] = ct[shortest] - bt_in[shortest] - at_in[shortest];
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        t++;
    }

    printf("\n==============================================");
    printf("\n           PREEMPTIVE SJF (SRTF)");
    printf("\n==============================================");
    printf("\nID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        tat[i] = bt_in[i] + wt[i];
        twt += wt[i];
        ttat += tat[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p_in[i], at_in[i], bt_in[i], ct[i], tat[i], wt[i]);
    }
    printf("\nAverage Waiting Time: %.2f", twt / n);
    printf("\nAverage Turnaround Time: %.2f\n", ttat / n);
}

int main()
{
    int n, at[20], bt[20], p[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        p[i] = i + 1;
        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
    }

    nonPreemptiveSJF(n, at, bt, p);
    preemptiveSJF(n, at, bt, p);

    return 0;
}