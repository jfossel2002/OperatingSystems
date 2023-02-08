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
void createNewPCBFromFile();
void createNewPCB();
void printPCB();
int searchForPCB(string name);
int PCBIndexSelect();
vector<ProcessControlBlock> PCBs;

void runMainMenu()
{
    // offers all the options for functionality of the program to the user
    system("clear");
    string rawUserInput;
    cout << "Please choose an option by entering the corresponding number...\n 1. View each PCB\n 2. View the process in a specific PCB\n"
         << " 3. Load  a process to a PCB from a text file\n 4. Create a new PCB with process in the terminal\n"
         << " 5. quit\n\n";
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
        runMainMenu();
    }

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
        createNewPCBFromFile();
        returnOrQuit();
        break;
    case 4:
        createNewPCB();
        returnOrQuit();
        break;
    case 5:
        cout << "exiting program...";
        exit(0);
        break;

    default:
        cout << "please enter a number corresponding to the given options!\npress enter to continue" << endl;
        cin.ignore(10, '\n');
        cin.get();
        runMainMenu();
        break;
    }
}

// Lists all PCBs
// CASE 1
void listPCBs()
{
    system("clear");
    for (int i = 0; i < PCBs.size(); i++)
    {
        cout << i + 1 << ". ID: " << PCBs[i].name << "\n";
    }
}

// Prints the process in a PCB
// CASE 2
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

// Case 3, orignally from PCB file
void createNewPCBFromFile()
{
    cout << "Please enter the file path to the file you would like to use\n\n";
    string path;
    cin >> path;
    string lineText;
    fstream newfile;
    newfile.open(path, ios::in); // open a file to perform read operation using file object
    if (newfile.is_open())
    { // checking whether the file is open
        while (getline(newfile, lineText))
        {                            // read data from file object and put it into string.
            ProcessControlBlock PCB; // Create new PCB
            if (PCB.loadFromLine(lineText))
            {                        // Put line of text file into new proccess
                PCBs.push_back(PCB); // Push new proccess onto end of proccess vector
            }
        }
        newfile.close(); // close the file object.
    }
    else
    {
        cout << "File does not exist";
    }
}

// Creates a new PCB from user input
// CASE 4
void createNewPCB()
{
    /*cout << "Please enter id of PCB\n\n";
    string name;
    cin >> name;
    int PCBIndex = searchForPCB(name);
    if (PCBIndex != -1)
    {
        cout << "PCB already found with id: " << name << "\n\n";
        return;
    }
    ProcessControlBlock PCB(name);
    PCBs.push_back(PCB);*/
    return;
}

// Helper to allows user to select a PCB by id
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

// Method to allow user to select another option or two quit the program
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
