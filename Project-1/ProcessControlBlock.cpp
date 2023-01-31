#include <iostream>
#include <fstream>
using namespace std;

class ProcessControlBlock {

    int id;
    int memory;
    int scheduling_information;
    int accounting_information;
    string process_state;
    string other_resources;

    // pointers will be needed for parent and child processes, open files, class?

    void readFromFile(string path) {
        ifstream datafileIfstream(path);

    }
};