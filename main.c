#include <stdio.h>

typedef struct{
    int pid; 
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
} Process;

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
    else{
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
            processes[i].remaining_time = processes[i].burst_time;
        }
        printf("Number of Processes: %d\n", count);
        printf("Process Data:\n");
        for(int i = 0; i < count; i++){
        printf("Process PID=%d, Arrival Time=%d, Burst Time=%d\n",
            processes[i].pid,
            processes[i].arrival_time,
            processes[i].burst_time);
    }
    }

    fclose(file);
    printf("File Closed Successfully.\n");

    return 0;
}