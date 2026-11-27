#ifndef SCHEDULER_H
#define SCHEDULER_H

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
} Process;

void spn(Process processes[], int n);

#endif