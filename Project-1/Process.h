#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <fstream>

using namespace std;

class Process
{
public:
    string fullString;

    int id;
    int cpu_state;
    int memory;
    int scheduling_information;
    int accounting_information;
    string process_state;
    string other_resources;
    string open_files; // TODO Change type

    int parent;
    int children;

    Process();
    void loadFromLine(string line);
    void to_string();
};

#endif