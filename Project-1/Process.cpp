#include <iostream>
#include <fstream>
#include <vector>
#include "Process.h"
using namespace std;

vector<Process> processes;

Process::Process() {};

void Process::loadFromLine(string line) {
    Process::testString = line;
}