
#include <stdio.h>
#include "campuscompute.h"
#include <stdlib.h>
void displayJobs(Job jobs[], int count) {
    if (count == 0) {
        printf("\nNo jobs available.\n");
        return;
    }

    printf("\nID\tArrival\tBurst\tPriority\tStatus\n");

    for (int i = 0; i < count; i++) {
        char *status;

        if (jobs[i].status == 0)
            status = "WAITING";
        else if (jobs[i].status == 1)
            status = "RUNNING";
        else
            status = "COMPLETED";

        printf("P%d\t%d\t%d\t%d\t\t%s\n",
               jobs[i].id, jobs[i].arrival,
               jobs[i].burst, jobs[i].priority, status);
    }
}

int main() {
    Job jobs[MAX_JOBS];
    int count = 0;
    int choice, quantum, nextID = 1;

    while (1) {
        printf("\n====================================\n");
        printf("       CAMPUSCOMPUTE MANAGER\n");
        printf("====================================\n");
        printf("1. Add Job\n");
        printf("2. Display Jobs\n");
        printf("3. FCFS Scheduling\n");
        printf("4. Round Robin Scheduling\n");
        printf("5. Priority Scheduling\n");
        printf("6. banker's algorithm\n");
	printf("7.exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            return 1;
        }

        switch (choice) {
            case 1:
                if (count >= MAX_JOBS) {
                    printf("Maximum job limit reached.\n");
                    break;
                }

                jobs[count].id = nextID++;
		jobs[count].status = 0;

                printf("Enter arrival time: ");
                if (scanf("%d", &jobs[count].arrival) != 1 ||
                    jobs[count].arrival < 0) {
                    printf("Invalid arrival time.\n");
                    return 1;
                }

                printf("Enter CPU burst time: ");
                if (scanf("%d", &jobs[count].burst) != 1 ||
                    jobs[count].burst <= 0) {
                    printf("Burst time must be positive.\n");
                    return 1;
                }

                printf("Enter priority (smaller number = higher priority): ");
                if (scanf("%d", &jobs[count].priority) != 1 ||
                    jobs[count].priority < 0) {
                    printf("Invalid priority.\n");
                    return 1;
                }

                count++;
                printf("Job added successfully!\n");
                break;

            case 2:
                displayJobs(jobs, count);
                break;

            case 3:
                if (count == 0)
                    printf("Add jobs first.\n");
                else
                    fcfs(jobs, count);
                break;

            case 4:
                if (count == 0) {
                    printf("Add jobs first.\n");
                    break;
                }

                printf("Enter time quantum: ");
                if (scanf("%d", &quantum) != 1 || quantum <= 0) {
                    printf("Invalid quantum.\n");
                    return 1;
                }

                roundRobin(jobs, count, quantum);
                break;

            case 5:
                if (count == 0)
                    printf("Add jobs first.\n");
                else
                    priorityScheduling(jobs, count);
                break;

	  case 6:
		bankerAlgorithm();
    		break;

	  case 7:
    		exit(0); 
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}
