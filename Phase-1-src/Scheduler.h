#include <vector>
#include <string>
#include "ProcessControlBlock.h"

using namespace std;

class Scheduler
{

private: 
    int penalty; //context switch penalty
    void makeSchedule(vector<ProcessControlBlock>sorted_PCBs);

public:
    Scheduler(int switch_penalty);
    void updatePenalty(int new_penalty);
    void FCFS(vector<ProcessControlBlock>PCBs); //   return schedule(?) and print start, stop, and turnaround times of each process and avg turnaround at the end
    void SJF(vector<ProcessControlBlock>PCBs);  
    void roundRobin(vector<ProcessControlBlock>PCBs,int quant); 
};
