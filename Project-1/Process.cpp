#include <iostream>
#include <fstream>
#include <vector>
#include "Process.h"
using namespace std;

vector<Process> processes;

Process::Process() {};

void Process::loadFromLine(string line) {
    Process::testString = line;
    vector<string> words;
    string currentWord = "";
    for (auto x : line)
    {
        if (x == ' ')
        {
            words.push_back(currentWord);
        }
        else
        {
            currentWord = currentWord + x;
        }
    }

    string idString = words[1];
    Process::id = stoi(idString);

    
}