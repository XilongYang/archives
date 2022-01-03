#include "pcb.h"
#include <iostream>

using std::to_string;
using std::cout;
using std::endl;

string PCB::curPID = "P1";

PCB::PCB(int priority, const string& name) : PID_(curPID), priority_(priority)
    ,runningTime(0),name_(name), blocked_(false)
{
    int pcbNum = stoi(string(curPID, 1));
    curPID = "P";
    curPID += to_string(pcbNum + 1);
}

void PCB::Block()
{
    blocked_ = false;
}
void PCB::WakeUp()
{
    blocked_ = false;
}
void PCB::Run()
{
    ++runningTime;
}

string PCB::GetPID() const
{
    return PID_;
}

void PCB::Show() const
{
    cout << std::boolalpha << "PID:" << PID_ << " Priority:" << priority_ 
        << " RunningTime:" << runningTime << " Blocked:" << blocked_ 
        << " Name:" << name_ << endl;
}

int PCB::GetPrior() const
{
    return priority_;
}

int PCB::GetTime() const
{
    return runningTime;
}