#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <cctype>
#include <string>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include "Scheduler.h"

using namespace std;

// declare methods here with no body to avoid undeclared identifier error
// use system("clear") to clear the screen at the beginning of your method an make things look nice
// system("clear") works on mac but might not on pc idk

void listPCBs();
void returnOrQuit();
void runMainMenu();
void createNewPCBFromFile();
void createNewPCB();
void printPCB();
int searchForPCB(string name);
int PCBIndexSelect();
void editPCB();
void runScheduler();
void editProcessData(int PCBIndex);
void deletePCB();
void editSchedVars();
void editSchedVarsLogic(int);
vector<ProcessControlBlock> PCBs;
Scheduler sched;
void runMainMenu()
{
    // offers all the options for functionality of the program to the user
    system("clear");
    string rawUserInput;
    cout << "Please choose an option by entering the corresponding number...\n 1. View each PCB\n 2. View the process in a specific PCB\n"
         << " 3. Load  a process to a PCB from a text file\n 4. Create a new PCB with process in the terminal\n"
         << " 5. Edit Data in PCB\n 6. Run Scheduler\n 7. Delete A PCB\n 8. Quit\n\n";
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
        return;
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
        editPCB();
        returnOrQuit();
        break;
    case 6:
        runScheduler();
        returnOrQuit();
        break;
    case 7:
        deletePCB();
        returnOrQuit();
        break;
    case 8:
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

// Helper to search the PCBs for a PCB by name/id return it's index if found, else returns -1
int searchForPCB(string name)
{
    for (int i = 0; i < PCBs.size(); i++)
    {
        if (PCBs[i].name == name)
        {
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
        { // read data from file object and put it into string.
            stringstream ss(lineText);
            string id;
            getline(ss, id, ' ');
            if (searchForPCB(id) != -1)
            {
                cout << "PCB already exists with ID: " << id << " this PCB has been skipped, please fix input and try again\n";
            }
            else
            {
                ProcessControlBlock PCB; // Create new PCB
                if (PCB.loadFromLine(lineText))
                {                        // Put line of text file into new proccess
                    PCBs.push_back(PCB); // Push new proccess onto end of proccess vector
                }
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
    string arr[11] = {"cpu_state", "memory", "scheduling_information", "accounting_information", "process_state", "parent", "children", "open_files", "other_resources", "arrival_time", "cpu_req"};
    string input_line;
    string temp;
    cout << "Input the id: ";
    getline(cin, temp);
    getline(cin, temp); // We need two of these idk why but without it, it breaks
    temp.erase(remove_if(temp.begin(), temp.end(), ::isspace), temp.end());
    if (searchForPCB(temp) != -1)
    {
        cout << "PCB already exists with this ID please try again\n";
        createNewPCB();
    }
    input_line += temp + " ";
    for (string name : arr)
    {
        cout << "Input the " << name << ": ";
        getline(cin, temp);
        temp.erase(remove_if(temp.begin(), temp.end(), ::isspace), temp.end());
        input_line += temp + " ";
    }
    cout << input_line;
    ProcessControlBlock PCB;
    PCB.loadFromLine(input_line);
    PCBs.push_back(PCB);
    return;
}

// Case 5, edit data in a PCB
void editPCB()
{
    int PCBIndex = PCBIndexSelect();
    system("clear");
    editProcessData(PCBIndex);
    return;
}

// Case 5, edit data in a PCB
// Handles all logic
void editProcessData(int PCBIndex)
{
    string options[12] = {"id", "cpu_state", "memory", "scheduling_information", "accounting_information", "process_state", "parent", "children", "open_files", "other_resources", "arrival_time", "cpu_req"};
    system("clear");
    cout << "Please select which attribute of the process you want to change, input the index\n";
    for (int i = 0; i < 12; i++)
    {
        cout << i + 1 << ". " << options[i] << "\n";
    }
    string rawUserInput;
    cin >> rawUserInput;
    int userInput;
    string newValue;
    try
    {
        userInput = stoi(rawUserInput);
        if (userInput < 0 or userInput > 12)
        {
            throw invalid_argument("");
        }
    }
    catch (...)
    {
        cout << "Invalid input\npress enter to retry"
             << endl;
        cin.ignore(10, '\n');
        cin.get();
        editProcessData(PCBIndex);
        return;
    }
    cout << "Please input what you want to change it to: ";
    cin >> newValue;
    if (userInput == 1)
    {
        if (searchForPCB(newValue) != -1)
        {
            cout << "PCB with ID: " << newValue << " already exists\npress enter to retry";
            cin.ignore(10, '\n');
            cin.get();
            editProcessData(PCBIndex);
            return;
        }
    }
    if (PCBs[PCBIndex].edit_process(userInput, newValue))
    {
        cout << "Value sucesfully changed";
    }
    else
    {
        editProcessData(PCBIndex);
    }
    return;
}

// Case 6

void runScheduler()
{
    
    cout << "\nPlease select which scheduler you want to run\n 1. First come first serve (FCFS)\n 2. Shortest job first(SJF)\n 3. FCFS and SJF\n 4. Round Robin\n";
    string selection;
    cin >> selection;
    int selectionInt;
    try
    {
        selectionInt = stoi(selection);
    }
    catch (...)
    {
        cout << "Invalid input\npress enter to retry"
             << endl;
        cin.ignore(10, '\n');
        cin.get();
        runScheduler();
        return;
    }
    if (selectionInt == 1)
    {
        sched.FCFS(PCBs);
    }
    else if (selectionInt == 2)
    {
        sched.SJF(PCBs);
    }
    else if (selectionInt == 3)
    {
        cout << "First Come First Serve:\n";
        sched.FCFS(PCBs);
        cout << "\n Shortest Job First:\n";
        sched.SJF(PCBs);
    }
    else if (selectionInt ==4)
    {
        sched.roundRobin(PCBs);
    }
    else
    {
        cout << "Invalid input\npress enter to retry"
             << endl;
        cin.ignore(10, '\n');
        cin.get();
        runScheduler();
        return;
    }
}

// Case 7
void deletePCB()
{
    cout << "Select a below PCB to delete: \n";
    int PCBIndex = PCBIndexSelect();
    system("clear");
    PCBs.erase(PCBs.begin() + PCBIndex);
    cout << "Sucesfully deleted PCB";
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
        returnOrQuit();
        return;
    }
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
    
        // ProcessControlBlock PCB_TEST_1;
        // PCB_TEST_1.name = "PCB1";
        // PCB_TEST_1.id = 1;
        // PCB_TEST_1.arrival_time = 1;
        // PCB_TEST_1.cpu_req = 3;

        // ProcessControlBlock PCB_TEST_2;
        // PCB_TEST_2.name = "PCB2";
        // PCB_TEST_2.id = 2;
        // PCB_TEST_2.arrival_time = 4;
        // PCB_TEST_2.cpu_req = 2;

        // ProcessControlBlock PCB_TEST_3;
        // PCB_TEST_3.name = "PCB3";
        // PCB_TEST_3.id = 3;
        // PCB_TEST_3.arrival_time = 3;
        // PCB_TEST_3.cpu_req = 9;

        // ProcessControlBlock PCB_TEST_4;
        // PCB_TEST_4.name = "PCB4";
        // PCB_TEST_4.id = 4;
        // PCB_TEST_4.arrival_time = 5;
        // PCB_TEST_4.cpu_req = 3;

        // PCBs.push_back(PCB_TEST_1);
        // PCBs.push_back(PCB_TEST_2);
        // //PCBs.push_back(PCB_TEST_3);
        // PCBs.push_back(PCB_TEST_4);


        // Scheduler sched ; 
        // sched.roundRobin(PCBs,2); 
        // //sched.FCFS(PCBs);
        // //sched.SJF(PCBs);
    
    runMainMenu();
    return 0;
};
