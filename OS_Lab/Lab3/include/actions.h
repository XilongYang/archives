#ifndef ACTION_H
#define ACTION_H

#include <memory>
#include <string>

using std::shared_ptr;
using std::string;


class Action
{
public:
    virtual void Run() = 0;
};

shared_ptr<Action> ActionFactory(const string& itemName);

#endif