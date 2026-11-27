#include <stdio.h>
#include "scheduler.h"

void spn(Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    int selected = -1; 
    int finished[100] = {0}; // Array to track completed processes
    int execution_order[201];
    int execution_start[201];
    int execution_end[201];
    int execution_count = 0;
    double total_turnaround_time = 0;
    double total_waiting_time = 0;
    double total_response_time = 0;
    double average_turnaround_time = 0;
    double average_waiting_time = 0;
    double average_response_time = 0;

    while(completed < n){
        selected = -1;  
        for (int i = 0; i < n; i++){
            if (processes[i].arrival_time <= current_time && !finished[i]) {
                if (selected == -1 || processes[i].burst_time < processes[selected].burst_time || 
                    (processes[i].burst_time == processes[selected].burst_time && processes[i].arrival_time < processes[selected].arrival_time) ||
                    (processes[i].burst_time == processes[selected].burst_time && processes[i].arrival_time == processes[selected].arrival_time && 
                    processes[i].pid < processes[selected].pid)) {
                    selected = i;
                }
            }
        }
        if (selected == -1) {
            int idle_start = current_time;
            int process_arrived; 
            // Advance time until at least one unfinished process arrives.
            do {
                current_time++;
                process_arrived = 0; 
                for (int i = 0; i < n; i++) {
                    if (!finished[i] && processes[i].arrival_time <= current_time) {
                        process_arrived = 1; 
                        break;
                    }
                }

            } while (process_arrived == 0);

            execution_order[execution_count] = -1;
            execution_start[execution_count] = idle_start;
            execution_end[execution_count] = current_time;
            execution_count++;

            continue;
        }
        else{
            int start_time = current_time;
            execution_order[execution_count] = selected;
            execution_start[execution_count] = start_time;
            current_time += processes[selected].burst_time;
            execution_end[execution_count] = current_time;
            execution_count++;
            completed++;
            finished[selected] = 1; // Mark the process as completed
            processes[selected].completion_time = current_time;
            processes[selected].turnaround_time = processes[selected].completion_time - processes[selected].arrival_time;
            processes[selected].waiting_time = processes[selected].turnaround_time - processes[selected].burst_time; 
            processes[selected].response_time = start_time - processes[selected].arrival_time;
            printf("Process %d: Completion Time = %d, Turnaround Time = %d, Waiting Time = %d, Response Time = %d\n", 
                processes[selected].pid, 
                processes[selected].completion_time,
                processes[selected].turnaround_time,    
                processes[selected].waiting_time,
                processes[selected].response_time
            );
        }
    }
    for (int i = 0; i < n; i++) {
        total_turnaround_time += processes[i].turnaround_time;
        total_waiting_time += processes[i].waiting_time;
        total_response_time += processes[i].response_time;
    }
    average_turnaround_time = total_turnaround_time / n;
    average_waiting_time = total_waiting_time / n;
    average_response_time = total_response_time / n;

    printf("Average Turnaround Time = %.2f\n", average_turnaround_time);
    printf("Average Waiting Time = %.2f\n", average_waiting_time);
    printf("Average Response Time = %.2f\n", average_response_time);

    printf("\n");

    printf("SPN Execution Order: \n");

    for (int i = 0; i < execution_count; i++) {

        if (execution_order[i] == -1) {
            printf("CPU IDLE Interval %d -> %d \n", execution_start[i], execution_end[i]);
        }
        else {
            printf("Process%d %d -> %d \n", execution_order[i], execution_start[i], execution_end[i]);
        }
    }
    printf("\n");
}