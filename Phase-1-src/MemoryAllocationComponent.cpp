#include <vector>
#include <string>
#include <iostream>
#include "ProcessControlBlock.h"

using namespace std;

class MemoryAllocationComponent
{
private:
    void compact() {
       for (int i = 0; i < allocations.size(); i++)
            {
                int hole_start = allocations[i].memory_location + allocations[i].memory;
                int hole_end = space_size;
                if (i == 0)
                {
                    allocations[i].memory_location = 0;
                }
                else
                {
                    allocations[i].memory_location = allocations[i - 1].memory_location 
                    + allocations[i - 1].memory + 1;
                }
            }
        }

public:
    int space_size = 16000;
    vector<ProcessControlBlock> allocations;

    void addFirstFit(ProcessControlBlock PCB) {
        if (allocations.size() == 0)
        {
            PCB.memory_location = 0;
            allocations.push_back(PCB);
            return;
        }
        else
        {
            for (int i = 0; i < allocations.size(); i++)
            {
                int hole_start = allocations[i].memory_location + allocations[i].memory;
                int hole_end = space_size;
                if (i + 1 < allocations.size())
                {
                    int hole_end = allocations[i + 1].memory_location;
                }
                int hole_size = hole_end - hole_start;
                if (hole_size >= PCB.memory) {
                    PCB.memory_location = hole_start;                 
                    allocations.insert(allocations.begin() + (i + 1), PCB);
                    return;
                }
            }
        }
        cout << "no space in memory found for PCB" << PCB.id;
    }

    void addWorstFit(ProcessControlBlock PCB)
    {
        if (allocations.size() == 0)
        {
            PCB.memory_location = 0;
            allocations.push_back(PCB);
            return;
        }
        else
        {
            int biggest_hole_location = 0;
            int biggest_hole_size = 0;
            for (int i = 0; i < allocations.size(); i++)
            {
                int hole_start = allocations[i].memory_location + allocations[i].memory;
                int hole_end = space_size;
                if (i + 1 < allocations.size())
                {
                    int hole_end = allocations[i + 1].memory_location;
                }
                int hole_size = hole_end - hole_start;
                if (hole_size > biggest_hole_size)
                {
                    biggest_hole_size = hole_size;
                    biggest_hole_location = hole_start;
                }
            }
            if (PCB.memory <= biggest_hole_size)
            {
                PCB.memory_location = biggest_hole_location;
            }
            else
            {
               cout << "no space in memory found for PCB" << PCB.id;
            }
        }
    }

    void removeProcess(ProcessControlBlock PCB)
    {
        for (int i = 0; i < allocations.size(); i++) {
            if (allocations[i].id == PCB.id)
            {
                allocations.erase(allocations.begin() + i);
            }
        }
    }
};