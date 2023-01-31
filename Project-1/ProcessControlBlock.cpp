#include <iostream>
#include <fstream>
#include <vector>
#include "Process.h"
#include "ProcessControlBlock.h"
using namespace std;

ProcessControlBlock::ProcessControlBlock() {};

void ProcessControlBlock::readFromFile(string path) {
    string lineText;
    ifstream datafileIfstream(path);
    while (getline(datafileIfstream, lineText)) {
        Process newProcess;
        newProcess.loadFromLine(lineText);
        processes.insert(processes.end() + 1, newProcess);
    }
}

void ProcessControlBlock::printProcesses() {
    for (int i = 0; i < processes.size(); i++) {
        cout << processes[i].testString << "\n";
    };
}
