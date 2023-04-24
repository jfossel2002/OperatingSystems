#include <vector>
#include <string>
#include "ProcessControlBlock.h"

using namespace std;

class MemoryAllocationComponent
{
private:
    void compact();

public:
    int space_size = 15000;
    vector<ProcessControlBlock> allocations;

    void addWorstFit(ProcessControlBlock PCB);
    void addFirstFit(ProcessControlBlock PCB);
    void removeProcess(ProcessControlBlock PCB);
    void printAllocations();
};