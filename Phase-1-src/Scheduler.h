#include <vector>
#include <string>
#include "ProcessControlBlock.h"

using namespace std;

class Scheduler
{

private:
    void makeSchedule(vector<ProcessControlBlock> sorted_PCBs);
    void makeRRSchedule(vector<ProcessControlBlock> sorted_PCBs);

public:
    void FCFS(vector<ProcessControlBlock> PCBs); //   return schedule(?) and print start, stop, and turnaround times of each process and avg turnaround at the end
    void SJF(vector<ProcessControlBlock> PCBs);
    void roundRobin(vector<ProcessControlBlock> PCBs);
};
