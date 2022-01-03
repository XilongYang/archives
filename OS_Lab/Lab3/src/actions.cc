#include "actions.h"
#include "menu.h"
#include "judge.h"
#include "used_table.h"
#include "free_table.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::shared_ptr;
using std::make_shared;
using std::runtime_error;

namespace {
    FreeTable& freeTable = FreeTable::GetInstance();
    UsedTable& usedTable = UsedTable::GetInstance();
}

class NoAction : public Action {
    virtual void Run() final {
        cout << "No action" << endl;
    }
};

class Allocate : public Action {
    virtual void Run() final {
        try {
            cout << "Input name: ";
            string name;
            getline(cin, name);
            cout << "Input size: ";
            string size;
            getline(cin, size);
            if(!IsNum(size)) {
                throw runtime_error("Input Error!");
            }
            auto space = freeTable.Malloc(std::stoi(size));
            usedTable.Malloc(UsedSpace(name, space));
        } catch (runtime_error r) {
            cout << r.what() << endl;
            Run();
        }
    }
};

class Free : public Action {
public:
    virtual void Run() final {
        cout << "Input name: ";
        string name;
        getline(cin, name);
        auto space = usedTable.Free(name);
        freeTable.Free(space);
    }
};

class Show : public Action {
public:
    virtual void Run() final {
        cout << "Free:" << endl;
        freeTable.Show();
        cout << endl << "Used:" << endl;
        usedTable.Show();
    };
};

shared_ptr<Action> ActionFactory(const string& itemName) {
    if(itemName == "Allocate") {
        return make_shared<Allocate>();
    }
    if(itemName == "Free") {
        return make_shared<Free>();
    }
    if(itemName == "Show") {
        return make_shared<Show>();
    }
    return make_shared<NoAction>();
}