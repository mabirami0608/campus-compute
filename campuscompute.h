#ifndef CAMPUSCOMPUTE_H
#define CAMPUSCOMPUTE_H

#define MAX_JOBS 100

typedef struct {
    int id;
    int arrival;
    int burst;
    int priority;
    int remaining;
    int completion;
    int first_start;
    int status;
} Job;

void displayJobs(Job jobs[], int count);
void fcfs(Job jobs[], int count);
void roundRobin(Job jobs[], int count, int quantum);
void priorityScheduling(Job jobs[], int count);
void bankerAlgorithm(void);
#endif

