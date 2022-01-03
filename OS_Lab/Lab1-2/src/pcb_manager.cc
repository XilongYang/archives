#include "pcb_manager.h"
#include <stdexcept>

using std::runtime_error;
using std::make_shared;

PCBManager PCBManager::instance_("NULL");

PCBManager& PCBManager::GetInstance()
{
    return instance_;
}

void PCBManager::Create(int priority, const string& name)
{
    ExculateAlgorithm();
    storage_->Push(make_shared<PCB>(priority, name));
}

void PCBManager::Block(const string& PID)
{
    ExculateAlgorithm();
    storage_->Block(PID);
}

void PCBManager::WakeUp(const string& PID)
{
    ExculateAlgorithm();
    storage_->WakeUp(PID);
}

void PCBManager::Stop(const string& PID)
{
    ExculateAlgorithm();
    storage_->Delete(PID);
}

void PCBManager::Show() 
{
    ExculateAlgorithm();
    storage_->Show();
}

void PCBManager::ChangeAlgorithm(const string& algor)
{
    algorithm_ = AlgorFactory(algor, storage_);
}

PCBManager::PCBManager(const string& algor)
: storage_(make_shared<PCBStorage>())
{
    algorithm_ = AlgorFactory(algor, storage_);
}

void PCBManager::ExculateAlgorithm()
{
    algorithm_->Execulate();
}