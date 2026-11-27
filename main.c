#include <stdio.h>
#include <ctype.h>
#include "scheduler.h"

int main(){
    FILE *file = fopen("processes.txt", "r");

    if(file == NULL){
        printf("Error opening file.\n");
        return 1;
    }
    printf("File Opened Successfully.\n");

    int count = 0;
    int result; 
    result = fscanf(file, "%d", &count);

    if(result != 1){
        printf("Error reading process count from file.\n");
        fclose(file);
        return 1;
    }

    if(count <= 0 || count > 100){
        printf("Invalid process count: %d. Must be between 1 and 100.\n", count);
        fclose(file);
        return 1;
    }
    
    Process processes[100] = {0};
    for (int i = 0; i < count; i++){
        result = fscanf(file, "%d %d %d", 
            &processes[i].pid, 
            &processes[i].arrival_time, 
            &processes[i].burst_time);
        if(result != 3){
            printf("Error reading process data for process %d.\n", i + 1);
            fclose(file);
            return 1;
        }
        if(processes[i].pid <= 0){
            printf("Invalid PID for process %d. Must be greater than 0.\n", i + 1);
            fclose(file);
            return 1;
        }
        if(processes[i].arrival_time < 0){
            printf("Invalid Arrival Time for process %d. Must be non-negative.\n", i + 1);
            fclose(file);
            return 1;
        }
        if(processes[i].burst_time <= 0){
            printf("Invalid Burst Time for process %d. Must be greater than 0.\n", i + 1);
            fclose(file);
            return 1;
        }
        for(int j = 0; j < i; j++){
            if(processes[i].pid == processes[j].pid){
                printf("Duplicate PID found for process %d. PID must be unique.\n", i + 1);
                fclose(file);
                return 1;
            }
        }
        processes[i].remaining_time = processes[i].burst_time;
    }
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (!isspace(ch)) {
            printf("Error: Unexpected extra data in input file.\n");
            fclose(file);
            return 1;
        }
    }

    printf("Number of Processes: %d\n", count);
    printf("Process Data:\n");
    for(int i = 0; i < count; i++){
        printf("Process PID=%d, Arrival Time=%d, Burst Time=%d\n",
            processes[i].pid,
            processes[i].arrival_time,
            processes[i].burst_time);
    }
    
    fclose(file);
    printf("File Closed Successfully.\n");

    spn(processes, count);

    return 0;
}