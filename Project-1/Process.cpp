#include <iostream>
#include <fstream>
using namespace std;

class Process {

    public:

        string testString;

        int id;
        int memory;
        int scheduling_information;
        int accounting_information;
        string process_state;
        string other_resources;

        Process* parent;
        Process* children[];

        //open files?

        Process() {}

        void loadFromLine(string line) {
            testString = line;
        }
};