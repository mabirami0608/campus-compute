
#include <stdio.h>
#include "campuscompute.h"
void updateStatus(Job jobs[], int count, int id, int status) {
    for (int i = 0; i < count; i++) {
        if (jobs[i].id == id) {
            jobs[i].status = status;
            return;
        }
    }
}
void printResults(Job jobs[], int count, const char *name) {
    float totalWT = 0, totalTAT = 0;

    printf("\n--- %s RESULTS ---\n", name);
    printf("ID\tAT\tBT\tPriority\tCT\tTAT\tWT\tRT\n");

    for (int i = 0; i < count; i++) {
        int tat = jobs[i].completion - jobs[i].arrival;
        int wt = tat - jobs[i].burst;
        int rt = jobs[i].first_start - jobs[i].arrival;

        totalWT += wt;
        totalTAT += tat;

        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n",
               jobs[i].id, jobs[i].arrival, jobs[i].burst,
               jobs[i].priority, jobs[i].completion, tat, wt, rt);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWT / count);
    printf("Average Turnaround Time: %.2f\n", totalTAT / count);
}

void fcfs(Job jobs[], int count) {
    Job temp[MAX_JOBS];

    for (int i = 0; i < count; i++)
        temp[i] = jobs[i];

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (temp[j].arrival > temp[j + 1].arrival ||
               (temp[j].arrival == temp[j + 1].arrival &&
                temp[j].id > temp[j + 1].id)) {
                Job t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
    }

    int time = 0;
    printf("\nGantt Chart:\n");

    for (int i = 0; i < count; i++) {
        if (time < temp[i].arrival)
            time = temp[i].arrival;

        temp[i].first_start = time;
	temp[i].status=1;

        printf("| P%d (%d-%d) ", temp[i].id,
               time, time + temp[i].burst);

        time += temp[i].burst;
        temp[i].completion = time;
	updateStatus(jobs, count, temp[i].id, 2);
	temp[i].status=2;

    }

    printf("|\n");
    printResults(temp, count, "FCFS");
}

void priorityScheduling(Job jobs[], int count) {
    Job temp[MAX_JOBS];
    int done[MAX_JOBS] = {0};

    for (int i = 0; i < count; i++)
        temp[i] = jobs[i];

    int time = 0, completed = 0;

    printf("\nGantt Chart:\n");

    while (completed < count) {
        int selected = -1;

        for (int i = 0; i < count; i++) {
            if (!done[i] && temp[i].arrival <= time) {
                if (selected == -1 ||
                    temp[i].priority < temp[selected].priority ||
                    (temp[i].priority == temp[selected].priority &&
                     (temp[i].arrival < temp[selected].arrival ||
                     (temp[i].arrival == temp[selected].arrival &&
                      temp[i].id < temp[selected].id)))) {
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            time++;
            continue;
        }

        temp[selected].first_start = time;
	temp[selected].status = 1;

        printf("| P%d (%d-%d) ", temp[selected].id,
               time, time + temp[selected].burst);

        time += temp[selected].burst;
        temp[selected].completion = time;
	updateStatus(jobs, count, temp[selected].id, 2);
	temp[selected].status = 2;
        done[selected] = 1;
        completed++;
    }

    printf("|\n");
    printResults(temp, count, "NON-PREEMPTIVE PRIORITY");
}

void roundRobin(Job jobs[], int count, int quantum) {
    Job temp[MAX_JOBS];
    int queue[10000];
    int visited[MAX_JOBS] = {0};

    int front = 0, rear = 0;
    int completed = 0, time = 0;

    if (quantum <= 0) {
        printf("Invalid time quantum.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        temp[i] = jobs[i];
        temp[i].remaining = jobs[i].burst;
        temp[i].first_start = -1;
    }

    printf("\nGantt Chart:\n");

    while (completed < count) {
        for (int i = 0; i < count; i++) {
            if (!visited[i] && temp[i].arrival <= time) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (front == rear) {
            time++;
            continue;
        }

        int current = queue[front++];
        int run = temp[current].remaining < quantum ?
                  temp[current].remaining : quantum;

        if (temp[current].first_start == -1)
            temp[current].first_start = time;

        printf("| P%d (%d-%d) ", temp[current].id,
               time, time + run);

        time += run;
        temp[current].remaining -= run;

        for (int i = 0; i < count; i++) {
            if (!visited[i] && temp[i].arrival <= time) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
	if (temp[current].remaining > 0) {
    queue[rear++] = current;
} else {
    temp[current].completion = time;
    updateStatus(jobs, count, temp[current].id, 2);
    completed++;
}
}
    printf("|\n");
    printResults(temp, count, "ROUND ROBIN");
}
