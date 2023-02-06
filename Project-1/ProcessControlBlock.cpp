#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Process.h"
#include "ProcessControlBlock.h"
using namespace std;

void ProcessControlBlock::readFromFile(string path)
{
    string lineText;
    fstream newfile;
    newfile.open(path, ios::in); // open a file to perform read operation using file object
    if (newfile.is_open())
    { // checking whether the file is open
        while (getline(newfile, lineText))
        {                                      // read data from file object and put it into string.
            Process newProcess;                // Create new proccess
            newProcess.loadFromLine(lineText); // Put line of text file into new proccess
            processes.push_back(newProcess);   // Push new proccess onto end of proccess vector
        }
        newfile.close(); // close the file object.
    }
}

void ProcessControlBlock::printProcesses() // Prints all entries in proccesses vector
{
    for (int i = 0; i < processes.size(); i++)
    {
        // cout << processes[i].fullString << "\n";
        processes[i].to_string();
    }
}
