#ifndef PCB_STORAGE_H
#define PCB_STORAGE_H

#include "pcb.h"
#include <memory>
#include <deque>
#include <string>

using std::shared_ptr;
using std::deque;
using std::string;

class PCBStorage
{
public:
    void  Run();
    void  Sort();
    void  ChangePCB();
    void  Block(const string& pid);
    void  WakeUp(const string& pid);
    void  Push(const shared_ptr<PCB>& pcb);
    void  Delete(const string& pid);
    shared_ptr<const PCB> GetRunningPCB();
    shared_ptr<const PCB> GetNextPCB();
    void  Show();
private:
    void PIDCheck(const string& PID);
    void SizeCheck(const deque<shared_ptr<PCB>>& que);
    deque<shared_ptr<PCB>> readys_;
    deque<shared_ptr<PCB>> blocks_;
    shared_ptr<PCB> running_;
    static const int max_size_;
};


#endif