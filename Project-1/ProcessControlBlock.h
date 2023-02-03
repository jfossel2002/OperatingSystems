#ifndef PROCESSCONTROLBLOCK_H
#define PROCESSCONTROLBLOCK_H

#include "Process.h"
#include <vector>
using namespace std;

class ProcessControlBlock {
    public:
    vector<Process> processes;
    ProcessControlBlock();
    void readFromFile(string path);
    void printProcesses();
};
#endif