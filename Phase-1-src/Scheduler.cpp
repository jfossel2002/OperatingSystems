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
// private
void Scheduler::makeSchedule(vector<ProcessControlBlock> sorted_PCBs, int choice)
{
    string finalString = "\n";
    vector<int> turnaround;
    int num_switches = 0;
    int start_time;
    int stop_time = 0;
    bool currentlyRunning = false;
    int proccessNumber = 0;
    bool scheduleRunning = true;
    int clockCycle = 0;
    int proccessCycles = 0;
    bool added = false;
    int totalCompactions = 0;
    vector<ProcessControlBlock> unallocatedPCBS = sorted_PCBs;
    while (scheduleRunning)
    {
        if (!currentlyRunning)
        {
            start_time = clockCycle;
            proccessCycles = sorted_PCBs[proccessNumber].cpu_req;
            if (proccessCycles > 0)
            {
                proccessCycles--;
            }
            currentlyRunning = true;
        }
        else if (currentlyRunning)
        {
            if (proccessCycles > 0)
            {

                proccessCycles--;
            }
            else // Proccess is done running
            {
                currentlyRunning = false;
                stop_time = clockCycle;
                turnaround.push_back(stop_time - sorted_PCBs[proccessNumber].arrival_time);
                num_switches++;
                finalString += "Process " + to_string(sorted_PCBs[proccessNumber].id) + ": start: " + to_string(start_time) + ", stop: " + to_string(stop_time) + ", turnaround: " + to_string(turnaround[proccessNumber]) + "\n";
                memoryAllocationComponent.removeProcess(sorted_PCBs[proccessNumber], clockCycle);
                if (memoryAllocationComponent.compact(clockCycle))
                {
                    totalCompactions++;
                }
                proccessNumber++;
                if (proccessNumber >= sorted_PCBs.size())
                {
                    scheduleRunning = false;
                    break;
                }
            }
        }
        for (ProcessControlBlock pcb : unallocatedPCBS)
        {
            if (pcb.arrival_time <= clockCycle)
            {
                if (choice == 1)
                {
                    added = memoryAllocationComponent.addFirstFit(pcb, clockCycle);
                }
                else
                {
                    added = memoryAllocationComponent.addWorstFit(pcb, clockCycle);
                }
                if (added)
                {
                    unallocatedPCBS.erase(unallocatedPCBS.begin());
                }
                else
                {
                    break;
                }
            }
        }
        clockCycle++;
    }
    cout << finalString << endl;
    cout << "Average turnaround: "
         << accumulate(turnaround.begin(), turnaround.end(), 0) / turnaround.size()
         << " Context Switches: " << num_switches - 1
         << endl;
    cout << "Total Compactions: " << totalCompactions << endl;
}

void Scheduler::makeScheduleSJF(vector<ProcessControlBlock> sorted_PCBs, int choice)
{
    string finalString = "\n";
    vector<int> turnaround;
    int num_switches = 0;
    int start_time;
    int stop_time = 0;
    bool currentlyRunning = false;
    int proccessNumber = 0;
    bool scheduleRunning = true;
    int clockCycle = 0;
    int proccessCycles = 0;
    bool added = false;
    int nextProccess = 0;
    int minJobRun = 999;
    int totalCompactions = 0;
    vector<ProcessControlBlock> unallocatedPCBS = sorted_PCBs;
    vector<ProcessControlBlock> memoryPCBS = sorted_PCBs;
    while (scheduleRunning)
    {
        for (int i = 0; i < unallocatedPCBS.size(); i++)
        {
            ProcessControlBlock pcb = unallocatedPCBS[i];
            if (pcb.arrival_time <= clockCycle)
            {
                if (choice == 1)
                {
                    added = memoryAllocationComponent.addFirstFit(pcb, clockCycle);
                }
                else
                {
                    added = memoryAllocationComponent.addWorstFit(pcb, clockCycle);
                }
                if (added)
                {
                    for (int i = 0; i < unallocatedPCBS.size(); i++)
                    {
                        if (unallocatedPCBS[i].id == pcb.id)
                        {
                            unallocatedPCBS.erase(unallocatedPCBS.begin() + i);
                        }
                    }
                }
                else
                {
                    break;
                }
            }
        }

        if (!currentlyRunning)
        {
            start_time = clockCycle;
            nextProccess = 0;
            minJobRun = 999;
            memoryPCBS = memoryAllocationComponent.getAllocations();
            for (int i = 0; i < memoryPCBS.size(); i++)
            {
                if (memoryPCBS[i].cpu_req < minJobRun)
                {
                    nextProccess = i;
                    minJobRun = memoryPCBS[i].cpu_req;
                }
            }
            proccessCycles = memoryPCBS[nextProccess].cpu_req; // Seg fault here on last process
            if (proccessCycles > 0)
            {
                proccessCycles--;
            }
            currentlyRunning = true;
        }
        else if (currentlyRunning)
        {
            if (proccessCycles > 0)
            {

                proccessCycles--;
            }
            else // Proccess is done running
            {
                currentlyRunning = false;
                stop_time = clockCycle;
                turnaround.push_back(stop_time - memoryPCBS[nextProccess].arrival_time);
                num_switches++;
                finalString += "Process " + to_string(memoryPCBS[nextProccess].id) + ": start: " + to_string(start_time) + ", stop: " + to_string(stop_time) + ", turnaround: " + to_string(turnaround[proccessNumber]) + "\n";
                memoryAllocationComponent.removeProcess(memoryPCBS[nextProccess], clockCycle);
                if (memoryAllocationComponent.compact(clockCycle))
                {
                    totalCompactions++;
                }
                proccessNumber++;
                if (proccessNumber >= sorted_PCBs.size())
                {
                    scheduleRunning = false;
                    break;
                }
            }
        }
        clockCycle++;
    }
    cout << finalString << endl;
    cout << "Average turnaround: "
         << accumulate(turnaround.begin(), turnaround.end(), 0) / turnaround.size()
         << " Context Switches: " << num_switches - 1
         << endl;
    cout << "Total Compactions: " << totalCompactions << endl;
}

void Scheduler::makeScheduleRR(vector<ProcessControlBlock> sorted_PCBs, int choice)
{
    string finalString = "\n";
    vector<int> turnaround;
    bool currentlyRunning = false;
    int proccessNumber = 0;
    bool scheduleRunning = true;
    int clockCycle = 0;
    int proccessCycles = 0;
    bool added = false;
    int totalCompactions = 0;
    vector<ProcessControlBlock> unallocatedPCBS = sorted_PCBs;
    // Other
    //  add PCBs to q, init tracker
    queue<ProcessControlBlock> q;
    queue<int> tracker;
    int num_switches = 1;
    int start_time;
    int stop_time = 0;
    ProcessControlBlock curr;
    int cpu_used;
    bool completed;
    while (scheduleRunning)
    {
        for (int i = 0; i < unallocatedPCBS.size(); i++)
        {
            ProcessControlBlock pcb = unallocatedPCBS[i];
            if (pcb.arrival_time <= clockCycle)
            {
                if (choice == 1)
                {
                    added = memoryAllocationComponent.addFirstFit(pcb, clockCycle);
                }
                else
                {
                    added = memoryAllocationComponent.addWorstFit(pcb, clockCycle);
                }
                if (added)
                {
                    for (int i = 0; i < unallocatedPCBS.size(); i++)
                    {
                        if (unallocatedPCBS[i].id == pcb.id)
                        {
                            q.push(unallocatedPCBS[i]);
                            tracker.push(0);
                            unallocatedPCBS.erase(unallocatedPCBS.begin() + i);
                        }
                    }
                }
                else
                {
                    break;
                }
            }
        }
        /*


        Itterate on one proccess
        */
        completed = false;
        curr = q.front();
        if (!currentlyRunning)
        {
            start_time = clockCycle;
            if (q.front().quantum > q.front().cpu_req)
            {
                proccessCycles = q.front().cpu_req;
            }
            else
            {
                proccessCycles = q.front().quantum;
            }
            if (proccessCycles > 0)
            {
                proccessCycles--;
            }
            currentlyRunning = true;
        }
        else if (currentlyRunning)
        {
            if (proccessCycles > 0)
            {
                proccessCycles--;
            }
            else // Proccess is done running
            {
                if (q.front().cpu_req > q.front().quantum) // NOT FULLY DONE
                {
                    currentlyRunning = false;
                    curr.cpu_req -= curr.quantum;
                    stop_time = clockCycle;
                    q.pop();
                    q.push(curr);
                    num_switches++;
                }
                else
                { // FULLY DONE
                    currentlyRunning = false;
                    stop_time = clockCycle;
                    q.pop();
                    // find turnaround
                    turnaround.push_back(stop_time - curr.arrival_time);
                    completed = true;
                    memoryAllocationComponent.removeProcess(curr, clockCycle);
                    if (memoryAllocationComponent.compact(clockCycle))
                    {
                        totalCompactions++;
                    }
                    num_switches++;
                    proccessNumber++;
                }
                finalString += "Process " + to_string(curr.id) + ": start: " + to_string(start_time) + ", stop: " + to_string(stop_time) + "\n";
                if (completed)
                {
                    finalString.pop_back();
                    finalString += ", turnaround: " + to_string(stop_time - curr.arrival_time) + "\n";
                }
                if (proccessNumber >= sorted_PCBs.size())
                {
                    num_switches--;
                    scheduleRunning = false;
                    break;
                }
            }
        }
        clockCycle++;
    }
    cout << finalString << endl;
    cout << "Average turnaround: "
         << (float)((int)(((float)accumulate(turnaround.begin(), turnaround.end(), 0) / (float)turnaround.size()) * 100)) / 100
         << ", Context Switches: " << num_switches - 1
         << endl;
    cout << "Total Compactions: " << totalCompactions << endl;
}

// public

void Scheduler::FCFS(vector<ProcessControlBlock> PCBs, int choice)
{
    // sort in ascending order of arrival time
    sort(PCBs.begin(), PCBs.end(),
         [](ProcessControlBlock &a, ProcessControlBlock &b)
         { return a.arrival_time < b.arrival_time; });

    makeSchedule(PCBs, choice);
}

void Scheduler::SJF(vector<ProcessControlBlock> PCBs, int choice)
{
    // sort in ascending order of job length
    sort(PCBs.begin(), PCBs.end(),
         [](ProcessControlBlock &a, ProcessControlBlock &b)
         { return a.arrival_time < b.arrival_time; });

    makeScheduleSJF(PCBs, choice);
}

void Scheduler::roundRobin(vector<ProcessControlBlock> PCBs, int choice)
{
    // start with fcfs order
    sort(PCBs.begin(), PCBs.end(),
         [](ProcessControlBlock &a, ProcessControlBlock &b)
         { return a.arrival_time < b.arrival_time; });

    makeScheduleRR(PCBs, choice);
}