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

void listPCBs();
void returnOrQuit();
void runMainMenu();
void loadPCBFromFile();
void loadDataToPCBFromFile();
void createNewPCB();
void printPCB();
int searchForPCB(string name);
vector<ProcessControlBlock> PCBs;

void runMainMenu()
{
    // offers all the options for functionality of the program to the user
    system("clear");
    string rawUserInput;
    cout << "Please choose an option by entering the corresponding number...\n 1. view each PCB\n 2. view the processes in a specific PCB\n"
         << " 3. load processes to a PCB from a text file\n 4. enter a process in the terminal to a PCB\n"
         << " 5. create a new PCB\n 6. quit\n\n";
    cin >> rawUserInput;
    int userInput = stoi(rawUserInput);

    switch (userInput)
    {
    case 1:
        listPCBs();
        returnOrQuit();
        break;
    case 2:
        printPCB();
        returnOrQuit();
        break;
    case 3:
        loadDataToPCBFromFile();
        returnOrQuit();
        break;
    case 4:

    case 5:
        createNewPCB();
        returnOrQuit();
        break;
    case 6:
        cout << "exiting program...";
        exit(0);
        break;

    default:
        cout << "please enter a number corresponding to the given options!\n press enter to continue";
        cin;
        runMainMenu();
        break;
    }
}

void returnOrQuit()
{
    cout << "\n\n";
    string rawUserInput;
    cout << "Would you like to...\n 1. return to the main menu\n 2. quit\n\n";
    cin >> rawUserInput;
    int userInput = stoi(rawUserInput);
    switch (userInput)
    {
    case 1:
        runMainMenu();
        break;
    case 2:
        cout << "exiting program...";
        exit(0);
        break;
    default:
        cout << "invalid input, please enter a 1 or a 2";
        returnOrQuit();
        break;
    }
}

int PCBIndexSelect()
{
    listPCBs();
    cout << "\nPlease select one of the following PCBs by entering it's corresponding number...\n";
    string rawUserInput;
    cin >> rawUserInput;
    int userInput;
    try
    {
        userInput = stoi(rawUserInput);
    }
    catch (...)
    {
        cout << "Invalid input\npress enter to retry"
             << endl;
        cin.ignore(10, '\n');
        cin.get();
        return PCBIndexSelect();
    }
    if (userInput <= PCBs.size() && userInput >= 0)
    {
        int PCBIndex = userInput - 1;
        cout << PCBs[PCBIndex].name << " has been selected\n";
        return userInput - 1;
    }
    else
    {
        cout << "Invalid input\npress enter to retry"
             << endl;
        cin.ignore(10, '\n');
        cin.get();
        ;

        return PCBIndexSelect();
    }
}

void listPCBs()
{
    system("clear");
    for (int i = 0; i < PCBs.size(); i++)
    {
        cout << i + 1 << ". " << PCBs[i].name << "\n";
    }
}

// Asks users for a file path and a PCB to load to, if both are found then the data is loaded into the PCB
void loadDataToPCBFromFile()
{
    int PCBIndex = PCBIndexSelect();
    cout << "Please enter the file path to the file you would like to use\n\n";
    string path;
    cin >> path;

    bool AddedData = PCBs[PCBIndex].readFromFile(path);
    if (AddedData)
    {
        cout << "Added Data to PCB" << PCBs[PCBIndex].name << "\n\n";
    }
}

// Creates a new PCB from a user input name and adds to the PCB vector
void createNewPCB()
{
    ProcessControlBlock PCB;
    cout << "Please enter name of PCB\n\n";
    string name;
    cin >> name;
    int PCBIndex = searchForPCB(name);
    if (PCBIndex != -1)
    {
        cout << "PCB already found with name: " << name << "\n\n";
        return;
    }
    PCB.name = name;
    PCBs.push_back(PCB);
    return;
}

// Prints the processes in a PCB
void printPCB()
{
    int PCBIndex = PCBIndexSelect();
    system("clear");
    PCBs[PCBIndex].printProcesses();
    return;
}

int searchForPCB(string name)
{
    for (int i = 0; i < PCBs.size(); i++)
    {
        if (PCBs[i].name == name)
        {
            PCBs[i].printProcesses();
            return i;
        }
    }
    return -1;
}

int main()
{
    // the following PCBs are for testing purposes

    ProcessControlBlock PCB69420;
    PCB69420.name = "PCB69420";
    ProcessControlBlock FossyFussy;
    FossyFussy.name = "FossyFussy";

    PCBs.push_back(PCB69420);
    PCBs.push_back(FossyFussy);

    runMainMenu();

    return 0;
};
