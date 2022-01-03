#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <initializer_list>
#include <memory>
#include "actions.h"

using std::string;
using std::vector;
using std::initializer_list;
using std::shared_ptr;

class Menu
{
public:
    Menu(const string& title, initializer_list<string> items);
    void Paint();
    void Run();
private:
    bool ChooseCheck(const string& choose);
    vector<shared_ptr<Action>> actions_;
    string title_;
    vector<string> items_;
};

#endif