#include "pcb_storage.h"
#include "judge.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

using std::sort;
using std::runtime_error;
using std::cout;
using std::endl;

const int PCBStorage::max_size_ = 10;

void PCBStorage::Run()
{
    running_->Run();
}

void PCBStorage::Sort()
{
    auto cmp = [](const shared_ptr<PCB>& a, const shared_ptr<PCB>& b)
    {
        return a->GetPrior() > b->GetPrior();
    };
    sort(readys_.begin(), readys_.end(), cmp);
}

void PCBStorage::ChangePCB()
{
    if(running_ != nullptr)
    {
        readys_.push_back(running_);
        running_ = nullptr;
    }
    if(readys_.empty()) return;
    running_ = readys_.front();
    readys_.pop_front();
}

void PCBStorage::Block(const string& pid)
{
    PIDCheck(pid);
    SizeCheck(blocks_);
    if(running_->GetPID() != pid)
    {
        throw(runtime_error("PCB not running"));
    }
    running_->Block();
    blocks_.push_back(running_);
    running_ = nullptr;
}

void PCBStorage::WakeUp(const string& pid)
{
    PIDCheck(pid);
    SizeCheck(readys_);
    for(auto i = blocks_.begin(); i != blocks_.end(); ++i)
    {
        if((*i)->GetPID() == pid)
        {
            (*i)->WakeUp();
            readys_.push_back(*i);
            blocks_.erase(i);
            return;
        }
    }
    throw(runtime_error("PCB not blocked"));
}

void PCBStorage::Push(const shared_ptr<PCB>& pcb)
{
    SizeCheck(readys_);
    readys_.push_back(pcb);;
}

void PCBStorage::Delete(const string& pid)
{
    PIDCheck(pid);
    if(running_->GetPID() == pid)
    {
        running_ = nullptr;
        return;
    }
    auto del = [pid](deque<shared_ptr<PCB>>& que)
    {
        for(auto i = que.begin(); i != que.end(); ++i)
        {
            if((*i)->GetPID() == pid)
            {
                que.erase(i);
                return 0;
            }
        }
        return 1;
    };
    if(!del(readys_)) return;
    if(!del(blocks_)) return;
    throw(runtime_error("PCB not found"));
}

shared_ptr<const PCB> PCBStorage::GetRunningPCB()
{
    return running_;
}

shared_ptr<const PCB> PCBStorage::GetNextPCB()
{
    return readys_.front();
}

void PCBStorage::Show()
{
    cout << "Running:" << endl;
    if(running_)
    {
        running_->Show();
    }
    cout << "Ready:" << endl;
    for(auto p : readys_)
    {
        p->Show();
    }
    cout << "Block:" << endl;
    for(auto p : blocks_)
    {
        p->Show();
    }
}

void PCBStorage::PIDCheck(const string& PID)
{
    if(!(PID.size() > 1 && PID[0] == 'P' && IsNum(string(PID, 1))))
    {
        throw(runtime_error("PID invalid"));
    }
}

void PCBStorage::SizeCheck(const deque<shared_ptr<PCB>>& que)
{
    if(que.size() >= max_size_)
    {
        throw(runtime_error("Out of size"));
    }
}