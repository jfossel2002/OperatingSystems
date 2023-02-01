#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <fstream>
using namespace std;

class Process {
    public:
    string testString;

    int id;
    int memory;
    int scheduling_information;
    int accounting_information;
    string process_state;
    string other_resources;

    Process* parent;
    Process* children[];

    Process();
    void loadFromLine(string line);
};


#endif