#include <stdio.h>

void firstFit(int blocks[], int b_count, int files[], int f_count)
{
    int allocation[20], temp_blocks[20];
    for (int i = 0; i < b_count; i++)
        temp_blocks[i] = blocks[i];
    for (int i = 0; i < f_count; i++)
        allocation[i] = -1;

    printf("\nFirst Fit Allocation Process:\n");
    for (int i = 0; i < f_count; i++)
    {
        for (int j = 0; j < b_count; j++)
        {
            if (temp_blocks[j] >= files[i])
            {
                allocation[i] = j;
                temp_blocks[j] -= files[i];
                break;
            }
        }
        if (allocation[i] != -1)
            printf("File %d (%d) -> Block %d\n", i + 1, files[i], allocation[i] + 1);
        else
            printf("File %d (%d) -> Not Allocated\n", i + 1, files[i]);
    }
}

void bestFit(int blocks[], int b_count, int files[], int f_count)
{
    int allocation[20], temp_blocks[20];
    for (int i = 0; i < b_count; i++)
        temp_blocks[i] = blocks[i];
    for (int i = 0; i < f_count; i++)
        allocation[i] = -1;

    printf("\nBest Fit Allocation Process:\n");
    for (int i = 0; i < f_count; i++)
    {
        int bestIdx = -1;
        for (int j = 0; j < b_count; j++)
        {
            if (temp_blocks[j] >= files[i])
            {
                if (bestIdx == -1 || temp_blocks[bestIdx] > temp_blocks[j])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1)
        {
            allocation[i] = bestIdx;
            temp_blocks[bestIdx] -= files[i];
            printf("File %d (%d) -> Block %d\n", i + 1, files[i], allocation[i] + 1);
        }
        else
        {
            printf("File %d (%d) -> Not Allocated\n", i + 1, files[i]);
        }
    }
}

void worstFit(int blocks[], int b_count, int files[], int f_count)
{
    int allocation[20], temp_blocks[20];
    for (int i = 0; i < b_count; i++)
        temp_blocks[i] = blocks[i];
    for (int i = 0; i < f_count; i++)
        allocation[i] = -1;

    printf("\nWorst Fit Allocation Process:\n");
    for (int i = 0; i < f_count; i++)
    {
        int worstIdx = -1;
        for (int j = 0; j < b_count; j++)
        {
            if (temp_blocks[j] >= files[i])
            {
                if (worstIdx == -1 || temp_blocks[worstIdx] < temp_blocks[j])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1)
        {
            allocation[i] = worstIdx;
            temp_blocks[worstIdx] -= files[i];
            printf("File %d (%d) -> Block %d\n", i + 1, files[i], allocation[i] + 1);
        }
        else
        {
            printf("File %d (%d) -> Not Allocated\n", i + 1, files[i]);
        }
    }
}

int main()
{
    int b_count, f_count;
    int blocks[20], files[20];

    printf("Enter the number of blocks: ");
    scanf("%d", &b_count);
    printf("Enter the size of each block: ");
    for (int i = 0; i < b_count; i++)
        scanf("%d", &blocks[i]);

    printf("Enter the number of files: ");
    scanf("%d", &f_count);
    printf("Enter the size of each file: ");
    for (int i = 0; i < f_count; i++)
        scanf("%d", &files[i]);

    firstFit(blocks, b_count, files, f_count);
    bestFit(blocks, b_count, files, f_count);
    worstFit(blocks, b_count, files, f_count);

    return 0;
}