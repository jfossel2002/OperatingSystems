#include <vector>
#include <string>
#include <iostream>
#include "ProcessControlBlock.h"
#include "MemoryAllocationComponent.h"

using namespace std;

bool MemoryAllocationComponent::compact(int cycle)
{
    for (int i = 0; i < allocations.size(); i++)
    {
        if (i == 0)
        {
            allocations[i].memory_location = 0;
            cout << "Cycle " << cycle << ": COMPACTION: PCB: " << allocations[i].id << " Reallocated to memory: " << allocations[i].memory_location << "-" << allocations[i].memory_location + allocations[i].memory - 1 << endl;
        }
        else
        {
            allocations[i].memory_location = allocations[i - 1].memory_location + allocations[i - 1].memory;
            cout << "Cycle " << cycle << ": COMPACTION: PCB: " << allocations[i].id << " reallocated to memory: " << allocations[i].memory_location << "-" << allocations[i].memory_location + allocations[i].memory - 1 << endl;
        }
    }
    if (allocations.size() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MemoryAllocationComponent::addFirstFit(ProcessControlBlock PCB, int cycle)
{
    if (allocations.size() == 0)
    {
        PCB.memory_location = 0;
        allocations.push_back(PCB);
        cout << "Cycle " << cycle << ": Allocated memory to PCB: " << PCB.id << " Location: " << PCB.memory_location << "-" << PCB.memory_location + PCB.memory - 1 << " size: " << PCB.memory << endl;
        return true;
    }
    else
    {
        int hole_start = allocations[allocations.size() - 1].memory_location + allocations[allocations.size() - 1].memory;
        int hole_end = space_size;
        if (allocations.size() < allocations.size())
        {
            int hole_end = allocations[allocations.size()].memory_location;
        }
        int hole_size = hole_end - hole_start;
        if (hole_size >= PCB.memory)
        {
            PCB.memory_location = hole_start;
            cout << "Cycle " << cycle << ": Allocated memory to PCB: " << PCB.id << " Location: " << PCB.memory_location << "-" << hole_start + PCB.memory - 1 << " size: " << PCB.memory << endl;
            allocations.push_back(PCB);
            return true;
        }
    }
    // cout << "no space in memory found for PCB" << PCB.id;
    return false;
}

bool MemoryAllocationComponent::addWorstFit(ProcessControlBlock PCB, int cycle)
{
    if (allocations.size() == 0)
    {
        PCB.memory_location = 0;
        allocations.push_back(PCB);
        cout << "Cycle " << cycle << ": Allocated memory to PCB: " << PCB.id << " Location: " << PCB.memory_location << "-" << PCB.memory_location + PCB.memory - 1 << " size: " << PCB.memory << endl;
        return true;
    }
    else
    {
        int biggest_hole_location = 0;
        int biggest_hole_size = 0;
        for (int i = 0; i < allocations.size(); i++)
        {
            int hole_start = allocations[i].memory_location + allocations[i].memory; // Start of free space
            int hole_end = space_size;                                               // End of all space
                                                                                     // cout << "Hole Start: " << hole_start << endl;
            // cout << "Hole End: " << hole_end << endl;
            if (i + 1 < allocations.size())
            {
                hole_end = allocations[i + 1].memory_location; // Start of next PCB in memory
                                                               //  cout << "Hole End updated: " << hole_end << endl;
            }
            int hole_size = hole_end - hole_start; // Size of free area
                                                   // cout << "Hole size: " << hole_size << endl;
            if (hole_size > biggest_hole_size)
            {
                biggest_hole_size = hole_size;      // Update where largest hole is
                biggest_hole_location = hole_start; // Location of biggest hole updated
                //    cout << "Biggest Hole Size updated: " << biggest_hole_size << endl;
                //   cout << "Biggest hole location updated: " << biggest_hole_location << endl;
            }
        }
        if (PCB.memory <= biggest_hole_size) // PCB can fit in biggest hole
        {
            PCB.memory_location = biggest_hole_location;
            cout << "Cycle " << cycle << ": Allocated memory to PCB: " << PCB.id << " Location: " << PCB.memory_location << "-" << PCB.memory_location + PCB.memory - 1 << " size: " << PCB.memory << endl;
            allocations.push_back(PCB);
            return true;
        }
        else
        {
            //   cout << "no space in memory found for PCB" << PCB.id;
            return false;
        }
    }
}

void MemoryAllocationComponent::removeProcess(ProcessControlBlock PCB, int cycle)
{
    for (int i = 0; i < allocations.size(); i++)
    {
        if (allocations[i].id == PCB.id)
        {
            cout << "Cycle " << cycle << ": Removed PCB: " << PCB.id << " freeing memory: " << PCB.memory_location << "-" << PCB.memory_location + PCB.memory - 1 << endl;
            allocations.erase(allocations.begin() + i);
        }
    }
}

void MemoryAllocationComponent::printAllocations()
{
    for (int i = 0; i < allocations.size(); i++)
    {
        std::cout << allocations.at(i).memory_location << ' ';
    }
}

vector<ProcessControlBlock> MemoryAllocationComponent::getAllocations()
{
    return allocations;
}