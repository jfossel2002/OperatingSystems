#include <vector>
#include <string>
#pragma once

using namespace std;

class ProcessControlBlock
{
public:
    string name;
    void invalid_input(string input_name, string input_value);
    void printProcesses();
    bool edit_process(int index, string newValue);

    string fullString;

    int id;
    int cpu_state;
    int memory;
    int scheduling_information;
    int accounting_information;
    string process_state;
    string other_resources;
    string open_files; // TODO Change type
    int arrival_time;
    int cpu_req;
    int quantum;
    int contextSwitch_penalty;

    int parent;
    int children;

    bool loadFromLine(string line);

    int memory_location;
};
