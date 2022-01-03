#include "actions.h"
#include "pcb_manager.h"
#include "menu.h"
#include "judge.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::shared_ptr;
using std::make_shared;
using std::invalid_argument;

namespace
{
    PCBManager& pcbs = PCBManager::GetInstance();
}
//==================Main========================
class NoAction : public Action
{
    virtual void Run() final 
    {
        cout << "No action" << endl;
    }
};

class CreatePCB : public Action
{
public:
    virtual void Run() final
    {
        cout << "Enter PCB priority(default = 0): ";
        string prior;
        getline(cin, prior);
        if(prior.empty())
        {
            prior = "0";
        }
        if(!IsNum(prior)) 
        {
            throw(invalid_argument("Input invalid!"));
        }
        cout << "Enter PCB name(default NULL): ";
        string name;
        getline(cin, name);
        if(name.empty())
        {
            name = "NULL";
        }
        pcbs.Create(stoi(prior), name);
        cout << "Create complete!" << endl;
    }
};

class BlockPCB : public Action
{
public:
    virtual void Run() final
    {
        cout << "Enter a PID to block PCB: ";
        string pid;
        getline(cin, pid);

        pcbs.Block(pid);
        cout << "Block complete" << endl;
    }
};

class WakeUpPCB : public Action
{
public:
    virtual void Run() final
    {
        cout << "Enter a PID to wake up PCB: ";
        string pid;
        getline(cin, pid);

        pcbs.WakeUp(pid);
        cout << "Wake up complete" << endl;
    }
};

class StopPCB : public Action
{
public:
    virtual void Run() final
    {
        cout << "Enter a PID to stop PCB: ";
        string pid;
        getline(cin, pid);

        pcbs.Stop(pid);
        cout << "Stop complete" << endl;
    }
};

class ShowPCB : public Action
{
public:
    virtual void Run() final
    {
        pcbs.Show();
    }
};

class SwitchAlgorithm : public Action
{
public:
    virtual void Run() final
    {
        Menu AlgorMenu("AlgorithmSwitch", 
        {"ChangeToRoundRobin", "ChangeToPriorityFirst"});
        AlgorMenu.Run();
    }
};

class ChangeToRoundRobin : public Action
{
public:
    virtual void Run() final
    {
        pcbs.ChangeAlgorithm("RoundRobin");
        cout << "Change to RoundRobin" << endl;
    }
};

class ChangeToPriorityFirst : public Action
{
public:
    virtual void Run() final
    {
        pcbs.ChangeAlgorithm("PriorityFirst");
        cout << "Change to PriorityFirst" << endl;
    }
};

shared_ptr<Action> ActionFactory(const string& itemName)
{
    if(itemName == "Create")
    {
        return make_shared<CreatePCB>();
    }
    if(itemName == "Block")
    {
        return make_shared<BlockPCB>();
    }
    if(itemName == "WakeUp")
    {
        return make_shared<WakeUpPCB>();
    }
    if(itemName == "Stop")
    {
        return make_shared<StopPCB>();
    }
    if(itemName == "Show")
    {
        return make_shared<ShowPCB>();
    }
    if(itemName == "SwitchAlgorithm")
    { 
        return make_shared<SwitchAlgorithm>();
    }
    if(itemName == "ChangeToRoundRobin")
    {
        return make_shared<ChangeToRoundRobin>();
    }
    if(itemName == "ChangeToPriorityFirst")
    {
        return make_shared<ChangeToPriorityFirst>();
    }
    return make_shared<NoAction>();
}