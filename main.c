#include <stdio.h>

struct Process{
    int pid; 
    int arrival_time;
    int burst_time;
    int remaining_time;
};

int main(){
    printf("Hello, World!\n");
    struct Process p1 = {1, 0, 8, 8};
    struct Process p2 = {2, 3, 5, 5};

    printf("Process PID=%d:, Arrival Time=%d, Burst Time=%d, Remaining Time=%d\n", p1.pid, p1.arrival_time, p1.burst_time, p1.remaining_time);
    printf("Process PID=%d:, Arrival Time=%d, Burst Time=%d, Remaining Time=%d\n", p2.pid, p2.arrival_time, p2.burst_time, p2.remaining_time);
    return 0;
}