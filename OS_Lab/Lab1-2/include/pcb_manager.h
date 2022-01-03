#ifndef PCB_MANAGER_H
#define PCB_MANAGER_H

#include "pcb.h"
#include "pcb_storage.h"
#include "scheduling_algorithm.h"
#include <memory>
#include <string>

using std::shared_ptr;
using std::unique_ptr;
using std::string;

class SchedulingAlgorithm;

class PCBManager
{
public:
    static PCBManager& GetInstance();
    void Create(int priority, const string& name);
    void Block(const string& PID);
    void WakeUp(const string& PID);
    void Stop(const string& PID);
    void Show();
    void ChangeAlgorithm(const string& algor);
private:
    PCBManager(const string& algor);
    PCBManager(const PCBManager&) = delete;
    PCBManager(PCBManager&&) = delete;
    void ExculateAlgorithm();
    unique_ptr<SchedulingAlgorithm> algorithm_;
    shared_ptr<PCBStorage> storage_;
    static PCBManager instance_;
};

#endif