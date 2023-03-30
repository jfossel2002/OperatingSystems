#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <numeric>
#include <iostream>
#include "Scheduler.h"



using namespace std;
//private
void Scheduler::makeSchedule(vector<ProcessControlBlock>sorted_PCBs)
{
    vector<int> turnaround;
    int num_switches= 0; 
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
        
         stop_time+=sorted_PCBs[i].contextSwitch_penalty;
         num_switches++; 
    }
    cout<<"Average turnaround: "
        << accumulate(turnaround.begin(),turnaround.end(),0) / turnaround.size()
        <<" Context Switches: " << num_switches-1
        <<endl;
}

void Scheduler::makeRRSchedule(vector<ProcessControlBlock>sorted_PCBs)
{   
    // add PCBs to q, init tracker 
    queue<ProcessControlBlock> q; 
    queue<int> tracker; 
    for(int i=0;i<sorted_PCBs.size();i++){
        q.push(sorted_PCBs[i]);
        tracker.push(0);
    }

    vector<int> turnaround;
    int num_switches=0; 
    int start_time;
    int stop_time = 0;
    ProcessControlBlock curr; 
    int cpu_used;
    bool completed;
    

    while (!q.empty())
    {

        completed = false;
        curr = q.front();
        cpu_used = tracker.front(); 
       
       if (stop_time>= curr.arrival_time){ // arrived before cpu available, schedule asap 
            start_time = stop_time; //curr start = previous stop
        }else{ //arrived while cpu available, upon arrival 
            start_time = curr.arrival_time;
        }

        if (cpu_used+curr.quantum >= curr.cpu_req){ //process completed
            stop_time = start_time + curr.cpu_req - cpu_used; 
            q.pop();
            tracker.pop();
            
            // find turnaround
            turnaround.push_back(stop_time - curr.arrival_time);
            completed = true;
        }else{
            stop_time = start_time + curr.quantum;
            q.pop();
            q.push(curr);
            tracker.pop();
            tracker.push(cpu_used+curr.quantum);
        }
        
        cout<<"Process "<<curr.id<<": start: "<<start_time
            <<", stop: "<<stop_time;
        if (completed){
            cout<<" Turnaround: "<<stop_time - curr.arrival_time<<"\n";
        }else{
            cout<<"\n"; 
        }
         stop_time+= curr.contextSwitch_penalty; 
        num_switches++;
    }
    cout<<"Average turnaround: "
        << accumulate(turnaround.begin(),turnaround.end(),0) / turnaround.size()
        <<", Context Switches: "<< num_switches-1
        <<endl;
}


//public


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

void Scheduler::roundRobin(vector<ProcessControlBlock>PCBs)
{
    //start with fcfs order
    sort(PCBs.begin(), PCBs.end(),
    [](ProcessControlBlock &a, ProcessControlBlock &b){return a.arrival_time < b.arrival_time;}); 

    makeRRSchedule(PCBs);
}