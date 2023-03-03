#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <iostream>
#include "Scheduler.h"


using namespace std;

void Scheduler::makeSchedule(vector<ProcessControlBlock>sorted_PCBs)
{
    vector<int> turnaround;
    int start_time;
    int stop_time = 0;  
    for(int i=0; i<static_cast<int>(sorted_PCBs.size()); i++){
        if (stop_time>= sorted_PCBs[i].arrival_time){ // arrived before cpu available, schedule asap 
            start_time = stop_time; //curr start = previous stop
        }else{ //arrived while cpu available, upon arrival 
            start_time = sorted_PCBs[i].arrival_time;
        }
        stop_time = start_time + sorted_PCBs[i].cpu_req; 
        turnaround.push_back(stop_time - sorted_PCBs[i].arrival_time);

        cout<<"Process "<<sorted_PCBs[i].id<<": start: "<<start_time
            <<", stop: "<<stop_time<<", turnaround: "<<turnaround[i]
            <<"\n"; 
    }
    cout<<"Average turnaround: "
        << accumulate(turnaround.begin(),turnaround.end(),0) / turnaround.size()
        <<endl;
}

Scheduler::Scheduler(int switch_penalty)
{
    updatePenalty(switch_penalty); 
}

void Scheduler::updatePenalty(int new_penalty)
{
    penalty = new_penalty;
}

void Scheduler::FCFS(vector<ProcessControlBlock>PCBs)
{
    // sort in ascending order of arrival time 
    sort(PCBs.begin(), PCBs.end(),
    [](ProcessControlBlock &a, ProcessControlBlock &b){return a.arrival_time < b.arrival_time;}); 

    makeSchedule(PCBs);
}

void Scheduler::SJF(vector<ProcessControlBlock>PCBs)
{

    //sort in ascending order of job length 
    sort(PCBs.begin(), PCBs.end(),
    [](ProcessControlBlock &a, ProcessControlBlock &b){return a.cpu_req < b.cpu_req;});

    makeSchedule(PCBs);
}

void Scheduler::roundRobin(vector<ProcessControlBlock>PCBs, int quant)
{
    //start with fcfs order
    sort(PCBs.begin(), PCBs.end(),
    [](ProcessControlBlock &a, ProcessControlBlock &b){return a.arrival_time < b.arrival_time;}); 


}