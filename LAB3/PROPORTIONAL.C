#include <stdio.h>

int main()
{
    int n, completed = 0;
    int id[20];
    float bt[20], rt[20], weight[20], total_weight = 0;
    float time_quantum, time = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        id[i] = i + 1;
        printf("P%d - Burst Time: ", id[i]);
        scanf("%f", &bt[i]);
        printf("P%d - Weight (Share): ", id[i]);
        scanf("%f", &weight[i]);
        rt[i] = bt[i];
        total_weight += weight[i];
    }

    printf("Enter Base Time Quantum: ");
    scanf("%f", &time_quantum);

    printf("\n--- Scheduling Execution ---\n");
    printf("Time\tProcess\tSlice\tRemaining\n-----------------------------------\n");

    while (completed < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (rt[i] > 0)
            {
                float slice = (weight[i] / total_weight) * time_quantum;

                if (slice > rt[i])
                {
                    slice = rt[i];
                }

                printf("%.2f\tP%d\t%.2f\t", time, id[i], slice);

                time += slice;
                rt[i] -= slice;

                if (rt[i] <= 0)
                {
                    rt[i] = 0;
                    completed++;
                    total_weight -= weight[i];
                    printf("DONE\n");
                }
                else
                {
                    printf("%.2f\n", rt[i]);
                }

                if (total_weight <= 0 && completed < n)
                {
                    total_weight = 0;
                    for (int j = 0; j < n; j++)
                        if (rt[j] > 0)
                            total_weight += weight[j];
                }
            }
        }
    }

    printf("\nTotal Simulation Time: %.2f\n", time);

    return 0;
}