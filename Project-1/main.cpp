#include <iostream>
#include <fstream>
#include <vector>

#include"Process.cpp"
#include"ProcessControlBlock.cpp"
using namespace std;

main() {
    cout << "Please enter the file path to the file you would like to use";
    string path;
    cin >> path;
    
    ProcessControlBlock PCB;
    PCB.readFromFile(path);
    PCB.printProcesses();
};