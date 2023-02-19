#include <vector>
#include <string>
#include "Scheduler.h"
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace std;

void Scheduler::makeSchedule(vector<ProcessControlBlock>sorted_PCBs)
{
    vector<int> turnaround;
    int start_time;
    int stop_time = 0;  
    for(int i=0; i<sorted_PCBs.size(); i++){
        if (stop_time>= sorted_PCBs[i].arrival_time){ // arrived before cpu available, schedule asap 
            start_time = stop_time; //curr start = previous stop
        }else{ //arrived while cpu available, upon arrival 
            start_time = sorted_PCBs[i].arrival_time;
        }
        stop_time = start_time + sorted_PCBs[i].cpu_req; 
        turnaround[i]= stop_time - sorted_PCBs[i].arrival_time;

        cout<<"Process "<<sorted_PCBs[i].id<<": start: "<<start_time<<", stop: "<<stop_time<<", turnaround: "<<turnaround[i]<<"\n"; 
    }
    cout<<"Average turnaround: "<< accumulate(sorted_PCBs.begin(),sorted_PCBs.end(),0) / sorted_PCBs.size()<<endl;
}

void Scheduler::FCFS(vector<ProcessControlBlock>PCBs)
{
     
    sort(PCBs.begin(), PCBs.end(),
    [](ProcessControlBlock * a, ProcessControlBlock * b){return b->arrival_time > a->arrival_time;}); 

    makeSchedule(PCBs);
    
}

void Scheduler::SJF(vector<ProcessControlBlock>PCBs)
{

    sort(PCBs.begin(), PCBs.end(),
    [](ProcessControlBlock * a, ProcessControlBlock * b){return b->cpu_req > a->cpu_req;});

    makeSchedule(PCBs);
}