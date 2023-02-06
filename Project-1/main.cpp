#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include "Process.h"
#include "ProcessControlBlock.h"
using namespace std;

// declare methods here with no body to avoid undeclared identifier error
// use system("clear") to clear the screen at the beginning of your method an make things look nice
// system("clear") works on mac but might not on pc idk

void listPCBs(vector<ProcessControlBlock> PCBs);
void returnOrQuit(vector<ProcessControlBlock> PCBs);
void runMainMenu(vector<ProcessControlBlock> PCBs);

void runMainMenu(vector<ProcessControlBlock> PCBs)
{
    //offers all the options for functionality of the program to the user
    system("clear");
    string rawUserInput;
    cout << "Please choose an option by entering the corresponding number...\n 1. view each PCB\n 2. view the processes in a specific PCB\n"
    << " 3. load processes to a PCB from a text file\n 4. enter a process in the terminal to a PCB\n"
    <<" 5. create a new PCB\n 6. quit\n\n";
    cin >> rawUserInput;
    int userInput = stoi(rawUserInput);

    switch (userInput) {
        case 1:
            listPCBs(PCBs);
            returnOrQuit(PCBs);
            break;
        case 2:

        case 3:

        case 4:

        case 5:

        case 6:
            cout << "exiting program...";
            exit(0);
            break;
        
        default:
            cout << "please enter a number corresponding to the given options!\n press enter to continue";
            cin;
            runMainMenu(PCBs);
            break;
    }
}

void returnOrQuit(vector<ProcessControlBlock> PCBs)
{
    cout << "\n\n";
    string rawUserInput;
    cout << "Would you like to...\n 1. return to the main menu\n 2. quit\n\n";
    cin >> rawUserInput;
    int userInput = stoi(rawUserInput);
    switch (userInput) {
        case 1:
            runMainMenu(PCBs);
            break;
        case 2:
            cout << "exiting program...";
            exit(0);
            break;
        default:
            cout << "invalid input, please enter a 1 or a 2";
            returnOrQuit(PCBs);
            break;
    }
}

void listPCBs(vector<ProcessControlBlock> PCBs)
{
    system("clear");
    for (int i = 0; i < PCBs.size(); i++)
    {
        cout << i + 1 << ". " << PCBs[i].name << "\n";
    }
}

int main()
{
    vector<ProcessControlBlock> PCBs;

    // the following PCBs are for testing purposes

    ProcessControlBlock PCB69420;
    PCB69420.name = "PCB69420";
    ProcessControlBlock FossyFussy;
    FossyFussy.name = "FossyFussy";

    PCBs.push_back(PCB69420); 
    PCBs.push_back(FossyFussy);

    runMainMenu(PCBs);

    /*
    cout << "Please enter the file path to the file you would like to use\n\n";
    string path;
    cin >> path;
    // cout << path;

    ProcessControlBlock PCB;
    PCB.readFromFile(path);
    PCB.printProcesses();
    */

    return 0;
};

