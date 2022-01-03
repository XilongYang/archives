#include "scheduling_algorithm.h"
#include <stdexcept>

using std::runtime_error;

SchedulingAlgorithm::SchedulingAlgorithm(shared_ptr<PCBStorage> pcb)
: storage_(pcb)
{
}

class NoAlgorithm : public SchedulingAlgorithm
{
public:
    NoAlgorithm(shared_ptr<PCBStorage> pcb) 
        : SchedulingAlgorithm(pcb) {}
    virtual void Execulate() override final
    {
        throw(runtime_error("No algorithm"));
    }
};

class RoundRobin : public SchedulingAlgorithm
{
public:
    RoundRobin(shared_ptr<PCBStorage> pcb) 
        : SchedulingAlgorithm(pcb),running(storage_->GetRunningPCB())
        , cur_time(0), limit_time(10)
    {
    }
    virtual void Execulate() override final
    {
        running = storage_->GetRunningPCB();
        if(!running || cur_time == limit_time)
        {
            storage_->ChangePCB();
            cur_time = 0;
        }
        else
        {
            storage_->Run();
            ++cur_time;
        }
    }
private:
    shared_ptr<const PCB> running;
    int cur_time;
    const int limit_time;
};

class PriorityFirst : public SchedulingAlgorithm
{
public:
    PriorityFirst(shared_ptr<PCBStorage> pcb) 
    : SchedulingAlgorithm(pcb) {}
    virtual void Execulate() override final
    {
        storage_->Sort();
        auto running = storage_->GetRunningPCB();
        auto next = storage_->GetNextPCB();
        if(running == nullptr 
            ||(next != nullptr && next->GetPrior() > running->GetPrior()))
        {
            storage_->ChangePCB();
        }
        else
        {
            storage_->Run();
        }
    }
};

unique_ptr<SchedulingAlgorithm> 
AlgorFactory(const string& algor, shared_ptr<PCBStorage> pcb)
{
    if(algor == "RoundRobin")
    {
        return unique_ptr<SchedulingAlgorithm>(new RoundRobin(pcb));
    }
    if(algor == "PriorityFirst")
    {
        return unique_ptr<SchedulingAlgorithm>(new PriorityFirst(pcb));
    }
    return unique_ptr<SchedulingAlgorithm>(new NoAlgorithm(pcb));
}