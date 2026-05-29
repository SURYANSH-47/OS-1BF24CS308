#include <stdio.h>

void display(int frames[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}

void fifo(int ref[], int n, int f)
{
    int frames[10], count = 0, PF = 0;
    for (int i = 0; i < f; i++)
        frames[i] = -1;

    printf("\nFIFO Page Replacement Process:\n");
    for (int i = 0; i < n; i++)
    {
        int found = 0;
        for (int j = 0; j < f; j++)
        {
            if (frames[j] == ref[i])
                found = 1;
        }
        if (!found)
        {
            frames[count] = ref[i];
            count = (count + 1) % f;
            PF++;
            printf("PF No. %d: ", PF);
            display(frames, f);
        }
    }
    printf("FIFO Page Faults: %d\n", PF);
}

void lru(int ref[], int n, int f)
{
    int frames[10], time[10], PF = 0;
    for (int i = 0; i < f; i++)
        frames[i] = -1;

    printf("\nLRU Page Replacement Process:\n");
    for (int i = 0; i < n; i++)
    {
        int found = 0;
        for (int j = 0; j < f; j++)
        {
            if (frames[j] == ref[i])
            {
                found = 1;
                time[j] = i; // Update last used time
            }
        }
        if (!found)
        {
            int pos = 0;
            if (i < f)
            {
                pos = i;
            }
            else
            {
                int min = time[0];
                for (int j = 1; j < f; j++)
                {
                    if (time[j] < min)
                    {
                        min = time[j];
                        pos = j;
                    }
                }
            }
            frames[pos] = ref[i];
            time[pos] = i;
            PF++;
            printf("PF No. %d: ", PF);
            display(frames, f);
        }
    }
    printf("LRU Page Faults: %d\n", PF);
}

void optimal(int ref[], int n, int f)
{
    int frames[10], PF = 0;
    for (int i = 0; i < f; i++)
        frames[i] = -1;

    printf("\nOptimal Page Replacement Process:\n");
    for (int i = 0; i < n; i++)
    {
        int found = 0;
        for (int j = 0; j < f; j++)
        {
            if (frames[j] == ref[i])
                found = 1;
        }
        if (!found)
        {
            int pos = -1;
            if (i < f)
            {
                pos = i;
            }
            else
            {
                int farthest = -1;
                for (int j = 0; j < f; j++)
                {
                    int k;
                    for (k = i + 1; k < n; k++)
                    {
                        if (frames[j] == ref[k])
                            break;
                    }
                    if (k > farthest)
                    {
                        farthest = k;
                        pos = j;
                    }
                }
            }
            frames[pos] = ref[i];
            PF++;
            printf("PF No. %d: ", PF);
            display(frames, f);
        }
    }
    printf("Optimal Page Faults: %d\n", PF);
}

int main()
{
    int n, f, ref[20];
    printf("Enter the number of Frames: ");
    scanf("%d", &f);
    printf("Enter the length of reference string: ");
    scanf("%d", &n);
    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &ref[i]);

    fifo(ref, n, f);
    lru(ref, n, f);
    optimal(ref, n, f);

    return 0;
}