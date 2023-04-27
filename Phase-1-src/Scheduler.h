#include <vector>
#include <string>
#include "ProcessControlBlock.h"

using namespace std;

class Scheduler
{

private:
    void makeSchedule(vector<ProcessControlBlock> sorted_PCBs, int choice);
    void makeScheduleSJF(vector<ProcessControlBlock> sorted_PCBs, int choice);
    void makeRRSchedule(vector<ProcessControlBlock> sorted_PCBs, int choice);

public:
    void FCFS(vector<ProcessControlBlock> PCBs, int choice); //   return schedule(?) and print start, stop, and turnaround times of each process and avg turnaround at the end
    void SJF(vector<ProcessControlBlock> PCBs, int choice);
    void roundRobin(vector<ProcessControlBlock> PCBs, int choice);
};
