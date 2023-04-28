#include <vector>
#include <string>
#include "ProcessControlBlock.h"

using namespace std;

class MemoryAllocationComponent
{
public:
    int space_size = 15000;
    vector<ProcessControlBlock> allocations;
    bool compact(int cycle);
    bool addWorstFit(ProcessControlBlock PCB, int cycle);
    bool addFirstFit(ProcessControlBlock PCB, int cycle);
    void removeProcess(ProcessControlBlock PCB, int cycle);
    void printAllocations();
    vector<ProcessControlBlock> getAllocations();
};