#include <stdio.h>

#define MAXP 10
#define MAXR 10

void bankerAlgorithm(void)
{
    int n, m;
    int allocation[MAXP][MAXR];
    int maximum[MAXP][MAXR];
    int need[MAXP][MAXR];
    int available[MAXR];
    int work[MAXR];
    int finish[MAXP] = {0};
    int safeSequence[MAXP];
    int completed = 0;

    printf("\nNumber of processes (1-10): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAXP) {
        printf("Invalid number of processes.\n");
        return;
    }

    printf("Number of resource types (1-10): ");
    if (scanf("%d", &m) != 1 || m < 1 || m > MAXR) {
        printf("Invalid number of resource types.\n");
        return;
    }

    printf("\nEnter available resources:\n");
    for (int j = 0; j < m; j++) {
        if (scanf("%d", &available[j]) != 1 || available[j] < 0) {
            printf("Invalid resource value.\n");
            return;
        }
    }

    printf("\nEnter Allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++) {
            if (scanf("%d", &allocation[i][j]) != 1 ||
                allocation[i][j] < 0) {
                printf("Invalid allocation value.\n");
                return;
            }
        }
    }

    printf("\nEnter Maximum matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++) {
            if (scanf("%d", &maximum[i][j]) != 1 ||
                maximum[i][j] < allocation[i][j]) {
                printf("Invalid maximum value.\n");
                return;
            }

            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    printf("\nNeed Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }

    for (int j = 0; j < m; j++)
        work[j] = available[j];

    while (completed < n) {
        int found = 0;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int possible = 1;

                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        possible = 0;
                        break;
                    }
                }

                if (possible) {
                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];

                    safeSequence[completed] = i;
                    finish[i] = 1;
                    completed++;
                    found = 1;
                }
            }
        }

        if (!found)
            break;
    }

    if (completed == n) {
        printf("\nSystem is in a SAFE state.\n");
        printf("Safe sequence: ");

        for (int i = 0; i < n; i++)
            printf("P%d%s", safeSequence[i],
                   i == n - 1 ? "\n" : " -> ");
    } else {
        printf("\nSystem is in an UNSAFE state.\n");
        printf("Processes unable to finish: ");

        for (int i = 0; i < n; i++) {
            if (!finish[i])
                printf("P%d ", i);
        }

        printf("\n");
    }
}

