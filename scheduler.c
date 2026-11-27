#include <stdio.h>
#include "scheduler.h"

void spn(Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    int selected = -1; 
    int finished[100] = {0}; // Array to track completed processes
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
        if (selected == -1){
            current_time++;
            continue;
        }
        else{
            int start_time = current_time;
            current_time += processes[selected].burst_time;
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
}