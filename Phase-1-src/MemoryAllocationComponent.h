#include <vector>
#include <string>
#include "ProcessControlBlock.h"

using namespace std;

class MemoryAllocationComponent
{
private:
    void compact();

public:
    vector<ProcessControlBlock> allocations;

    void addWorstFit(ProcessControlBlock PCB);
    void addFirstFit(ProcessControlBlock PCB);
    void removeProcess(ProcessControlBlock PCB);
};