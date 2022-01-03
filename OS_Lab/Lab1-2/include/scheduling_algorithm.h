#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "pcb_storage.h"
#include <memory>
#include <string>

using std::shared_ptr;
using std::unique_ptr;
using std::string;

class PCBManager;

class SchedulingAlgorithm
{
public:
    SchedulingAlgorithm(shared_ptr<PCBStorage> storage);
    virtual void Execulate() = 0;
protected:
    shared_ptr<PCBStorage> storage_;
};

unique_ptr<SchedulingAlgorithm> 
AlgorFactory(const string& name, shared_ptr<PCBStorage> pcb);

#endif