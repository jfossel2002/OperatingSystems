#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <string>

#include "ProcessControlBlock.h"

using namespace std;

void ProcessControlBlock::printProcesses() // Prints all entries in proccesses vector
{
    cout << "ID: " << id << "\n";
    cout << "cpu_state: " << cpu_state << "\n";
    cout << "memory: " << memory << "\n";
    cout << "scheduling_information: " << scheduling_information << "\n";
    cout << "accounting_information: " << accounting_information << "\n";
    cout << "process_state: " << process_state << "\n";
    cout << "parent: " << parent << "\n";
    cout << "children: " << children << "\n";
    cout << "open_files: " << open_files << "\n";
    cout << "other_resources: " << other_resources << "\n\n";
}

/*
Takes in the entire process line and splits it into each of the 10 required components
For example: 1 0 2000 1 0 "new" NULL NULL NULL "NONE"
Is split into Id: 0, cpu_state: 0, memory: 2000, scheduling_information: 1, accounting_information: 0
proccess_state = "new", parent: NULL, children: NULL, open_files: NULL, other_resources: "NONE"
*/
void ProcessControlBlock::loadFromLine(string line)
{
    ProcessControlBlock::fullString = line;
    stringstream ss(fullString);
    string s;
    getline(ss, s, ' ');
    name = s;
    id = stoi(s);
    getline(ss, s, ' ');
    cpu_state = stoi(s);
    getline(ss, s, ' ');
    memory = stoi(s);
    getline(ss, s, ' ');
    scheduling_information = stoi(s);
    getline(ss, s, ' ');
    accounting_information = stoi(s);
    getline(ss, s, ' ');
    process_state = s;
    getline(ss, s, ' ');
    parent = stoi(s);
    getline(ss, s, ' ');
    children = stoi(s);
    getline(ss, s, ' ');
    open_files = s;
    getline(ss, s, ' ');
    other_resources = s;
}