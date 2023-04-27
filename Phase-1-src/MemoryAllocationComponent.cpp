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
            cout << "COMPACTION: PCB: " << allocations[i].id << " Reallocated to memory start: " << allocations[i].memory_location << " end: " << allocations[i].memory_location + allocations[i].memory << " at cycle: " << cycle << endl;
        }
        else
        {
            allocations[i].memory_location = allocations[i - 1].memory_location + allocations[i - 1].memory + 1;
            cout << "COMPACTION: PCB: " << allocations[i].id << " reallocated to memory start: " << allocations[i].memory_location << " end: " << allocations[i].memory_location + allocations[i].memory << " at cycle: " << cycle << endl;
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

bool MemoryAllocationComponent::addFirstFit(ProcessControlBlock PCB)
{
    if (allocations.size() == 0)
    {
        PCB.memory_location = 0;
        allocations.push_back(PCB);
        cout << "Starts at location: " << PCB.memory_location << " and has size " << PCB.memory;
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
            cout << "Starts at location: " << hole_start << " and has size " << PCB.memory;
            PCB.memory_location = hole_start;
            allocations.insert(allocations.begin() + (allocations.size()), PCB);
            return true;
        }
    }
    // cout << "no space in memory found for PCB" << PCB.id;
    return false;
}

bool MemoryAllocationComponent::addWorstFit(ProcessControlBlock PCB)
{
    if (allocations.size() == 0)
    {
        PCB.memory_location = 0;
        allocations.push_back(PCB);
        cout << "Starts at location: " << PCB.memory_location << " and has size " << PCB.memory;
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
            cout << "Starts at location: " << biggest_hole_location << " and has size " << PCB.memory;
            PCB.memory_location = biggest_hole_location;
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

void MemoryAllocationComponent::removeProcess(ProcessControlBlock PCB)
{
    for (int i = 0; i < allocations.size(); i++)
    {
        if (allocations[i].id == PCB.id)
        {
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