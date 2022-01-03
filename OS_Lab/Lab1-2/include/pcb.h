#ifndef PCB_H
#define PCB_H

#include <string>

using std::string;

class PCB
{
public:
    PCB(int priority, const string& name);
    void Block();
    void WakeUp();
    void Run();
    void Show() const;
    string GetPID() const;
    int GetPrior() const;
    int GetTime() const;
private:
    string PID_;
    int priority_;
    int runningTime;
    string name_;
    bool blocked_;
    static string curPID;
};

#endif