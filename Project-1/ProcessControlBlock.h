using namespace std;
#include "Process.h"
#include <vector>

class ProcessControlBlock
{
public:
    vector<Process> processes;
    void readFromFile(string path);
    void printProcesses();
};
