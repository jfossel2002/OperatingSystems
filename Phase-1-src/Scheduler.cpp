#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <numeric>
#include <iostream>
#include "Scheduler.h"
#include "MemoryAllocationComponent.h"

using namespace std;

MemoryAllocationComponent memoryAllocationComponent;
int cycle_counter = 0;
// private
void Scheduler::makeSchedule(vector<ProcessControlBlock> sorted_PCBs, int choice)
{
    vector<int> turnaround;
    int num_switches = 0;
    int start_time;
    int stop_time = 0;
    MemoryAllocationComponent memory_component; // instance of memory class component

    for (int i = 0; i < static_cast<int>(sorted_PCBs.size()); i++)
    {

        if (stop_time >= sorted_PCBs[i].arrival_time)
        {                           // arrived before cpu available, schedule asap
            start_time = stop_time; // curr start = previous stop
        }
        else
        { // arrived while cpu available, upon arrival
            start_time = sorted_PCBs[i].arrival_time;
        }
        stop_time = start_time + sorted_PCBs[i].cpu_req;
        turnaround.push_back(stop_time - sorted_PCBs[i].arrival_time);

        cout << "Process " << sorted_PCBs[i].id << ": start: " << start_time
             << ", stop: " << stop_time << ", turnaround: " << turnaround[i]
             << "\n";
        // include the memory allocation component
        if (sorted_PCBs[i].memory > 0)
        {
            if (choice == 1)
            {
                memoryAllocationComponent.addFirstFit(sorted_PCBs[i]);
            }
            else
            {
                memoryAllocationComponent.addWorstFit(sorted_PCBs[i]);
            }
            memoryAllocationComponent.removeProcess(sorted_PCBs[i]);
        }
        else
        {
            cout << "Process " << sorted_PCBs[i].id << " has no memory requirements" << endl;
        }

        stop_time += sorted_PCBs[i].contextSwitch_penalty;
        num_switches++;
    }
    cout << "Average turnaround: "
         << accumulate(turnaround.begin(), turnaround.end(), 0) / turnaround.size()
         << " Context Switches: " << num_switches - 1
         << endl;
    cycle_counter++;
}

void Scheduler::makeRRSchedule(vector<ProcessControlBlock> sorted_PCBs, int choice)
{
    // add PCBs to q, init tracker
    /*
    I.e. for the 3 different phase 2/3 algs FCFS, SJF, and RR, we need to add in the memory mangements algs. 
    This consists of making it so when a process arrives it gets allocated memory (using one of the two Phase 4 algs),
    if there is no room in memory then it needs to wait. When a process completes running it needs to be removed memory 
    and compaction should occur  
    */
    queue<ProcessControlBlock> q;
    queue<int> tracker;
    for (int i = 0; i < sorted_PCBs.size(); i++)
    {
        q.push(sorted_PCBs[i]);
        tracker.push(0);
    }

    vector<int> turnaround;
    int num_switches = 1;
    int start_time;
    int stop_time = q.front().contextSwitch_penalty;
    ProcessControlBlock curr;
    int cpu_used;
    bool completed;

    while (!q.empty())
    {

        completed = false;
        curr = q.front();
        cpu_used = tracker.front();

        if (stop_time >= curr.arrival_time)
        {                           // arrived before cpu available, schedule asap
            start_time = stop_time; // curr start = previous stop
        }
        else
        { // arrived while cpu available, upon arrival
            start_time = curr.arrival_time;
        }

        if (cpu_used + curr.quantum >= curr.cpu_req)
        { // process completed
            stop_time = start_time + curr.cpu_req - cpu_used;
            q.pop();
            tracker.pop();

            // find turnaround
            turnaround.push_back(stop_time - curr.arrival_time);
            completed = true;
        }
        else
        {
            stop_time = start_time + curr.quantum;
            q.pop();
            q.push(curr);
            tracker.pop();
            tracker.push(cpu_used + curr.quantum);
        }

        cout << "Process " << curr.id << ": start: " << start_time
             << ", stop: " << stop_time;
        if (completed)
        {
            cout << " Turnaround: " << stop_time - curr.arrival_time << "\n";
        }
        else
        {
            cout << "\n";
        }
        stop_time += curr.contextSwitch_penalty;
        num_switches++;
    }
    cout << "Average turnaround: "
         << (float)((int)(((float)accumulate(turnaround.begin(), turnaround.end(), 0) / (float)turnaround.size()) * 100)) / 100
         << ", Context Switches: " << num_switches - 1
         << endl;
}

// public
#define MEMORY_SIZE 1024
void Scheduler::FCFS(vector<ProcessControlBlock> PCBs, int choice)
{
    // sort in ascending order of arrival time
    sort(PCBs.begin(), PCBs.end(),
         [](ProcessControlBlock &a, ProcessControlBlock &b)
         { return a.arrival_time < b.arrival_time; });

    // memory management
    int memory_size = MEMORY_SIZE; // total memory size
    vector<int> memory; // keep track of free memory blocks
    memory.push_back(memory_size);

        for (ProcessControlBlock pcb : PCBs) {
        // if there is enough memory, allocate it
        if (pcb.memory_req <= memory[0]) {
            pcb.memory_location = memory_size - memory[0];
            memory[0] -= pcb.memory_req;
        } else {
            // not enough memory, wait until there is
            pcb.state = "WAITING"; // that means the process is waiting for memory
        }
    }

    // compact memory by merging free blocks
    vector<int> new_memory;
    for (int block : memory) {
        if (new_memory.empty() || new_memory.back() + block == memory_size) {
            new_memory.back() += block;
        } else {
            new_memory.push_back(block);
        }
    }

    memory = new_memory;

    makeSchedule(PCBs, choice);
}

void Scheduler::SJF(vector<ProcessControlBlock> PCBs, int choice)
{
    // sort in ascending order of job length
    sort(PCBs.begin(), PCBs.end(),
         [](ProcessControlBlock &a, ProcessControlBlock &b)
         { return a.cpu_req < b.cpu_req; });

    makeSchedule(PCBs, choice);
}

void Scheduler::roundRobin(vector<ProcessControlBlock> PCBs, int choice)
{
    // start with fcfs order
    sort(PCBs.begin(), PCBs.end(),
         [](ProcessControlBlock &a, ProcessControlBlock &b)
         { return a.arrival_time < b.arrival_time; });

    makeRRSchedule(PCBs, choice);
}