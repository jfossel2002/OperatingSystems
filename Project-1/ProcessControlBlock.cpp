#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Process.h"
#include "ProcessControlBlock.h"
#include <sstream>
#include <string>

using namespace std;
void ProcessControlBlock::printProcesses() // Prints the procces stored in the PCB
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
Handles invalid inputs
*/
bool ProcessControlBlock::loadFromLine(string line)
{
    ProcessControlBlock::fullString = line;
    stringstream ss(fullString);
    string s;
    try
    {
        getline(ss, s, ' ');
        name = s;
        id = stoi(s);
    }
    catch (...)
    {
        invalid_input("id", s);
        return false;
    }
    try
    {
        getline(ss, s, ' ');
        cpu_state = stoi(s);
        return false;
    }
    catch (...)
    {
        invalid_input("cpu_state", s);
        return false;
    }
    try
    {
        getline(ss, s, ' ');
        memory = stoi(s);
    }
    catch (...)
    {
        invalid_input("memory", s);
        return false;
    }
    try
    {
        getline(ss, s, ' ');
        scheduling_information = stoi(s);
    }
    catch (...)
    {
        invalid_input("scheduling_information", s);
        return false;
    }
    try
    {
        getline(ss, s, ' ');
        accounting_information = stoi(s);
    }
    catch (...)
    {
        invalid_input("accounting_information", s);
        return false;
    }
    getline(ss, s, ' ');
    process_state = s;
    try
    {
        getline(ss, s, ' ');
        parent = stoi(s);
    }
    catch (...)
    {
        invalid_input("parent", s);
        return false;
    }
    try
    {
        getline(ss, s, ' ');
        children = stoi(s);
    }
    catch (...)
    {
        invalid_input("children", s);
        return false;
    }
    getline(ss, s, ' ');
    open_files = s;
    getline(ss, s, ' ');
    other_resources = s;
    return true;
}

void ProcessControlBlock::invalid_input(string input_name, string input_value)
{
    cout << "The " << input_name << ": " << input_value << " is not a valid " << input_name << " please verify your input is an interger and within range.\nYhe PCB has not been created.";
}
