#include <iostream>
#include <fstream>
#include <vector>
#include "Process.h"
#include "ProcessControlBlock.h"
using namespace std;

int main() {
    cout << "Please enter the file path to the file you would like to use\n\n";
    string path;
    cin >> path;
    cout << path;

    ProcessControlBlock PCB;
    PCB.readFromFile("../test.txt");
    PCB.printProcesses();

    return 0;
};