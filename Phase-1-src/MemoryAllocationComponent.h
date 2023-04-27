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
    bool addWorstFit(ProcessControlBlock PCB);
    bool addFirstFit(ProcessControlBlock PCB);
    void removeProcess(ProcessControlBlock PCB);
    void printAllocations();
    vector<ProcessControlBlock> getAllocations();
};