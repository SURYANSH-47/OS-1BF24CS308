#include <stdio.h>

int main() {
    int n, r, i, j, k;

    printf("Enter number of processes\n");
    scanf("%d", &n); 

    printf("Enter number of resources\n");
    scanf("%d", &r); 

    int alloc[n][r], max[n][r], need[n][r];
    int avail[r], finish[n], safe[n];

    for(i = 0; i < n; i++) {
        printf("\nEnter details for P%d\n", i);
        printf("Enter allocation\n");
        for(j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);

        printf("Enter Max\n");
        for(j = 0; j < r; j++) {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    printf("\nEnter Available Resources\n");
    for(i = 0; i < r; i++)
        scanf("%d", &avail[i]);

    int pid;
    int request[r];
    printf("\nEnter New Request Details --\n Enter pid\n ");
    scanf("%d", &pid);

    printf("Enter Request for Resources\n");
    for(i = 0; i < r; i++) {
        scanf("%d", &request[i]);
    }

    int can_grant = 1;
    for(i = 0; i < r; i++) {
        if(request[i] > need[pid][i] || request[i] > avail[i]) {
            can_grant = 0;
            break;
        }
    }

    if(can_grant) {
        for(i = 0; i < r; i++) {
            avail[i] -= request[i];
            alloc[pid][i] += request[i];
            need[pid][i] -= request[i];
        }
    } else {
        printf("\nRequest cannot be granted immediately.\n");
    }

    for(i = 0; i < n; i++)
        finish[i] = 0;

    int count = 0;
    printf("\nOUTPUT\n");

    while(count < n) {
        int found = 0;
        for(i = 0; i < n; i++) {
            if(!finish[i]) {
                for(j = 0; j < r; j++)
                    if(need[i][j] > avail[j])
                        break;

                if(j == r) {
                    for(k = 0; k < r; k++)
                        avail[k] += alloc[i][k];

                    printf("P%d is visited(", i);
                    for(k = 0; k < r; k++)
                        printf("%d", avail[k]);
                    printf(")\n");

                    safe[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if(!found) break;
    }

    if(count == n) {
        printf("\nSYSTEM IS IN SAFE STATE\n");
        printf("The Safe Sequence is (");
        for(i = 0; i < n; i++) {
            printf("P%d%s", safe[i], (i == n - 1) ? "" : " ");
        }
        printf(")\n");
    } else {
        printf("\nSYSTEM IS NOT IN SAFE STATE\n");
        printf("Processes causing deadlock: ");
        for(i = 0; i < n; i++) {
            if(finish[i] == 0) printf("P%d ", i);
        }
        printf("\n");
    }

    return 0;
}