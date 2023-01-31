#include <iostream>
#include <fstream>
#include <vector>

#include"Process.cpp"
using namespace std;

class ProcessControlBlock {
    public:
        vector<Process> processes;

        void readFromFile(string path) {
            string lineText;
            ifstream datafileIfstream(path);
            while (getline(datafileIfstream, lineText)) {
                Process newProcess;
                newProcess.loadFromLine(lineText);
                processes.insert(processes.end() + 1, newProcess);
            }
        }

        void printProcesses() {
            for (int i = 0; i < processes.size(); i++) {
                cout << processes[i].testString << "\n";
            };
        }
};