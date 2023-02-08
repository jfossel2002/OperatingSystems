using namespace std;
#include "Process.h"
#include <vector>

class ProcessControlBlock
{
public:
    string name;
    bool readFromFile(string path);
    void printProcesses();

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

    void loadFromLine(string line);
    void to_string();
    void loadFromLine();
};
