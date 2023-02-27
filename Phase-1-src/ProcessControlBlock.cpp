#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "ProcessControlBlock.h"
#include <sstream>
#include <string>
#include <map>
#include <any>

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
    try
    {
        getline(ss, s, ' ');
        arrival_time = stoi(s); 
    }
    catch(...)
    {
        invalid_input("arrival_time", s);
        return false;
    }
    try
    {
        getline(ss, s, ' ');
        cpu_req = stoi(s); 
    }
    catch(...)
    {
        invalid_input("cpu_req", s);
        return false;
    }
    
    return true;
}

void ProcessControlBlock::invalid_input(string input_name, string input_value)
{
    cout << "The " << input_name << ": " << input_value << " is not a valid " << input_name << " please verify your input is an interger and within range.\nYhe PCB has not been created.";
}

bool ProcessControlBlock::edit_process(int index, string newValue)
{
    string options[10] = {"id", "cpu_state", "memory", "scheduling_information", "accounting_information", "process_state", "parent", "children", "open_files", "other_resources"};
    try
    {
        switch (index)
        {
        case 1:
            cout << "Old value of id: " << id << "\nNew value of id: " << newValue << "\n";
            id = stoi(newValue);
            name = newValue;
            break;
        case 2:
            cout << "Old value of cpu_state: " << cpu_state << "\nNew value of cpu_state: " << newValue << "\n";
            cpu_state = stoi(newValue);
            break;
        case 3:
            cout << "Old value of memory: " << memory << "\nNew value of memory: " << newValue << "\n";
            memory = stoi(newValue);
            break;
        case 4:
            cout << "Old value of scheduling_information: " << scheduling_information << "\nNew value of scheduling_information: " << newValue << "\n";
            scheduling_information = stoi(newValue);
            break;
        case 5:
            cout << "Old value of accounting_information: " << accounting_information << "\nNew value of accounting_information: " << newValue << "\n";
            accounting_information = stoi(newValue);
            break;
        case 6:
            cout << "Old value of process_state: " << process_state << "\nNew value of process_state: " << newValue << "\n";
            process_state = newValue;
            break;
        case 7:
            cout << "Old value of parent: " << parent << "\nNew value of parent: " << newValue << "\n";
            parent = stoi(newValue);
            break;
        case 8:
            cout << "Old value of children: " << children << "\nNew value of children: " << newValue << "\n";
            children = stoi(newValue);
            break;
        case 9:
            cout << "Old value of open_files: " << open_files << "\nNew value of open_files: " << newValue << "\n";
            open_files = newValue;
            break;
        case 10:
            cout << "Old value of other_resources: " << open_files << "\nNew value of other_resources: " << newValue << "\n";
            open_files = newValue;
            break;
        default:
            cout << "please enter a number corresponding to the given options!\npress enter to continue" << endl;
            cin.ignore(10, '\n');
            cin.get();
            edit_process(index, newValue);
            break;
        }
    }
    catch (...)
    {
        cout << "Invalid input value\npress enter to retry"
             << endl;
        cin.ignore(10, '\n');
        cin.get();
        return false;
    }
    return true;
}
