#include <stdio.h>
#include <stdlib.h>

void allowOne(int hungryCount, int positions[])
{
    printf("\nAllow one philosopher to eat at any time\n");
    for (int i = 0; i < hungryCount; i++)
    {
        for (int j = 0; j < hungryCount; j++)
        {
            printf("P %d is waiting\n", positions[j]);
        }
        printf("P %d is granted to eat\n", positions[i]);
        printf("P %d has finished eating\n", positions[i]);
    }
}

void allowTwo(int hungryCount, int positions[], int total)
{
    printf("\nAllow two philosophers to eat at any time\n");
    int i, j, found = 0;

    for (i = 0; i < hungryCount; i++)
    {
        for (j = i + 1; j < hungryCount; j++)
        {
            int p1 = positions[i];
            int p2 = positions[j];

            int diff = abs(p1 - p2);
            if (diff != 1 && diff != (total - 1))
            {
                printf("\nCombination %d and %d\n", p1, p2);
                printf("P %d and P %d are granted to eat\n", p1, p2);
                printf("P %d and P %d have finished eating\n", p1, p2);
                found = 1;
            }
        }
    }

    if (!found)
    {
        printf("\nNo two philosophers can eat simultaneously (all are neighbors).\n");
    }
}

int main()
{
    int totalPhilo, hungryCount, choice;
    int positions[10];

    printf("Enter the total number of philosophers: ");
    scanf("%d", &totalPhilo);

    printf("How many are hungry: ");
    scanf("%d", &hungryCount);

    for (int i = 0; i < hungryCount; i++)
    {
        printf("Enter philosopher %d position (1 to %d): ", i + 1, totalPhilo);
        scanf("%d", &positions[i]);
    }

    while (1)
    {
        printf("\n1. One can eat at a time");
        printf("\n2. Two can eat at a time");
        printf("\n3. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            allowOne(hungryCount, positions);
            break;
        case 2:
            allowTwo(hungryCount, positions, totalPhilo);
            break;
        case 3:
            exit(0);
        default:
            printf("\nInvalid choice!");
        }
    }
    return 0;
}