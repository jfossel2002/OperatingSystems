using namespace std;
#include "Process.h"
#include <vector>

class ProcessControlBlock
{
public:
    string name;
    vector<Process> processes;
    bool readFromFile(string path);
    void printProcesses();
};
