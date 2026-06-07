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

void sortTasks(int n, int id[], int ci[], int ti[])
{
    int temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (ti[j] > ti[j + 1])
            {
                temp = ti[j];
                ti[j] = ti[j + 1];
                ti[j + 1] = temp;
                temp = ci[j];
                ci[j] = ci[j + 1];
                ci[j + 1] = temp;
                temp = id[j];
                id[j] = id[j + 1];
                id[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int n, hyper_period = 1;
    int id[20], ci[20], ti[20], ri[20];
    float utilization = 0.0, bound;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        id[i] = i + 1;
        printf("Task %d - Execution Time (Ci): ", i + 1);
        scanf("%d", &ci[i]);
        printf("Task %d - Period (Ti): ", i + 1);
        scanf("%d", &ti[i]);
        ri[i] = 0;
        utilization += (float)ci[i] / ti[i];

        if (i == 0)
            hyper_period = ti[i];
        else
            hyper_period = findLCM(hyper_period, ti[i]);
    }

    bound = n * (pow(2, 1.0 / n) - 1);
    printf("\n--- Analysis ---\n");
    printf("Utilization: %.4f\n", utilization);
    printf("RMS Bound: %.4f\n", bound);
    printf("Hyper-period (LCM): %d\n", hyper_period);

    if (utilization <= bound)
    {
        printf("Status: Schedulable\n");
    }
    else
    {
        printf("Status: Not guaranteed (Utilization > Bound)\n");
    }

    sortTasks(n, id, ci, ti);

    printf("\n--- Schedule Table ---\n");
    printf("Time\tProcess\n----------------\n");
    for (int t = 0; t < hyper_period; t++)
    {
        int active = -1;

        for (int i = 0; i < n; i++)
        {
            if (t % ti[i] == 0)
            {
                ri[i] = ci[i];
            }
        }

        for (int i = 0; i < n; i++)
        {
            if (ri[i] > 0)
            {
                active = i;
                break;
            }
        }

        if (active != -1)
        {
            printf("%d\tExecuting P%d\n", t, id[active]);
            ri[active]--;
        }
        else
        {
            printf("%d\tIdle\n", t);
        }
    }

    return 0;
}