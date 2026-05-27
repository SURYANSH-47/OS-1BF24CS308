#include <stdio.h>
#include <math.h>

int findGCD(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int findLCM(int a, int b)
{
    if (a == 0 || b == 0)
        return 0;
    return (a * b) / findGCD(a, b);
}

int main()
{
    int n, hyper_period = 1;
    int id[20], ci[20], ti[20], di[20], ri[20], current_deadline[20];
    float utilization = 0.0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        id[i] = i + 1;
        printf("\nProcess P%d:\n", id[i]);
        printf("  Execution Time (Ci): ");
        scanf("%d", &ci[i]);
        printf("  Period (Ti): ");
        scanf("%d", &ti[i]);
        printf("  Relative Deadline (Di): ");
        scanf("%d", &di[i]);

        ri[i] = 0;
        current_deadline[i] = 0;

        /* Utilization is calculated based on Period */
        utilization += (float)ci[i] / ti[i];

        if (i == 0)
            hyper_period = ti[i];
        else
            hyper_period = findLCM(hyper_period, ti[i]);
    }

    printf("\n--- Analysis ---\n");
    printf("CPU Utilization (U): %.4f\n", utilization);

    if (utilization > 1.0)
    {
        printf("Status: Not feasible (U > 1)\n");
    }
    else
    {
        printf("Status: Schedulable (Pending deadline checks per cycle)\n");
    }
    printf("Simulation Length (Hyper-period): %d\n", hyper_period);

    printf("\nTime\tExecution\tActive Deadline\n----------------------------------------------\n");
    for (int t = 0; t < hyper_period; t++)
    {

        /* Arrival Logic: Process arrives at the start of every Period Ti */
        for (int i = 0; i < n; i++)
        {
            if (t % ti[i] == 0)
            {
                /* If ri > 0, the previous instance missed its deadline */
                if (ri[i] > 0 && t > 0)
                {
                    printf("\n[!] Deadline Missed for P%d at time %d\n", id[i], t);
                }
                ri[i] = ci[i];
                current_deadline[i] = t + di[i];
            }
        }

        int selected = -1;
        int min_deadline = 1e9;

        /* Selection Logic: Pick ready process with the Earliest Absolute Deadline */
        for (int i = 0; i < n; i++)
        {
            if (ri[i] > 0)
            {
                if (current_deadline[i] < min_deadline)
                {
                    min_deadline = current_deadline[i];
                    selected = i;
                }
            }
        }

        if (selected != -1)
        {
            printf("%d\tExecuting P%d\tDeadline: %d\n", t, id[selected], current_deadline[selected]);
            ri[selected]--;
        }
        else
        {
            printf("%d\tIdle\n", t);
        }
    }

    return 0;
}