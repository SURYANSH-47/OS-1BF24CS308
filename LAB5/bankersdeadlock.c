#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10
#define MAX_R 10

void bankersAlgorithm()
{
    int n, m, i, j, k;
    int alloc[MAX_P][MAX_R], max[MAX_P][MAX_R], need[MAX_P][MAX_R], avail[MAX_R];
    int work[MAX_R], safeSeq[MAX_P];
    bool finish[MAX_P] = {false};

    printf("\n--- Banker's Algorithm (Deadlock Avoidance) ---\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Max Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - alloc[i][j];
        }

    printf("Enter Available Resources: ");
    for (i = 0; i < m; i++)
    {
        scanf("%d", &avail[i]);
        work[i] = avail[i];
    }

    int count = 0;
    while (count < n)
    {
        bool found = false;
        for (i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool possible = true;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        possible = false;
                        break;
                    }
                }
                if (possible)
                {
                    for (k = 0; k < m; k++)
                        work[k] += alloc[i][k];
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found)
            break;
    }

    if (count == n)
    {
        printf("\nSYSTEM IS IN SAFE STATE\nSafe Sequence: ");
        for (i = 0; i < n; i++)
            printf("P%d ", safeSeq[i]);
        printf("\n");
    }
    else
    {
        printf("\nSYSTEM IS IN UNSAFE STATE\n");
    }
}

void deadlockDetection()
{
    int n, m, i, j, k;
    int alloc[MAX_P][MAX_R], request[MAX_P][MAX_R], avail[MAX_R], work[MAX_R];
    bool finish[MAX_P] = {false};

    printf("\n--- Deadlock Detection Algorithm ---\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
    {
        int rowSum = 0;
        for (j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
            rowSum += alloc[i][j];
        }
        finish[i] = (rowSum == 0);
    }

    printf("Enter Request Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &request[i][j]);

    printf("Enter Available Resources: ");
    for (i = 0; i < m; i++)
    {
        scanf("%d", &avail[i]);
        work[i] = avail[i];
    }

    bool progress = true;
    while (progress)
    {
        progress = false;
        for (i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool canGrant = true;
                for (j = 0; j < m; j++)
                {
                    if (request[i][j] > work[j])
                    {
                        canGrant = false;
                        break;
                    }
                }
                if (canGrant)
                {
                    for (k = 0; k < m; k++)
                        work[k] += alloc[i][k];
                    finish[i] = true;
                    progress = true;
                }
            }
        }
    }

    bool deadlock = false;
    printf("\nResults:");
    for (i = 0; i < n; i++)
    {
        if (!finish[i])
        {
            if (!deadlock)
                printf("\nSystem is in DEADLOCK STATE\nDeadlocked processes: ");
            printf("P%d ", i);
            deadlock = true;
        }
    }
    if (!deadlock)
        printf("\nNo Deadlock Detected.");
    printf("\n");
}

int main()
{
    int choice;
    while (1)
    {
        printf("\n1. Banker's Algorithm (Avoidance)\n2. Deadlock Detection\n3. Exit\nChoice: ");
        scanf("%d", &choice);
        if (choice == 1)
            bankersAlgorithm();
        else if (choice == 2)
            deadlockDetection();
        else
            break;
    }
    return 0;
}