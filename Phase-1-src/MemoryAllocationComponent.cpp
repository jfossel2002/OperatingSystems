#include <vector>
#include <string>
#include <iostream>
#include "ProcessControlBlock.h"
#include "MemoryAllocationComponent.h"

using namespace std;

void MemoryAllocationComponent::compact()
{
    for (int i = 0; i < allocations.size(); i++)
    {
        if (i == 0)
        {
            allocations[i].memory_location = 0;
        }
        else
        {
            allocations[i].memory_location = allocations[i - 1].memory_location + allocations[i - 1].memory + 1;
        }
    }
}

void MemoryAllocationComponent::addFirstFit(ProcessControlBlock PCB)
{
    if (allocations.size() == 0)
    {
        PCB.memory_location = 0;
        allocations.push_back(PCB);
        cout << "\t Starts at location: " << PCB.memory_location << "\n\t and has size " << PCB.memory_location + PCB.memory << "\n"
             << endl;
        return;
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
        cout << "\t Starts at location: " << hole_start << "\n\t and has size " << hole_start + PCB.memory << "\n"
             << endl;
        if (hole_size >= PCB.memory)
        {
            PCB.memory_location = hole_start;
            allocations.insert(allocations.begin() + (allocations.size()), PCB);
            return;
        }
    }
    cout << "no space in memory found for PCB" << PCB.id;
}

void MemoryAllocationComponent::addWorstFit(ProcessControlBlock PCB)
{
    if (allocations.size() == 0)
    {
        PCB.memory_location = 0;
        allocations.push_back(PCB);
        cout << "\t Starts at location: " << PCB.memory_location << "\n\t and has size " << PCB.memory_location + PCB.memory << "\n"
             << endl;
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
            cout << "\n\t Starts at location: " << hole_start << "\n\t and has size " << hole_start + PCB.memory << "\n"
                 << endl;
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