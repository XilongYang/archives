#include "menu.h"
#include "judge.h"
#include <iostream>

using namespace std;


#ifdef __linux__
    #define CLS system("clear");
#endif

#ifdef _WIN32
    #define CLS system("cls");
#endif

const string space = "    ";

Menu::Menu(const string& title, initializer_list<string> items)
    : title_(space + space + title), actions_(1, nullptr), items_() {
    int i = 1;
    for(auto s : items) {
        items_.push_back(string(space + to_string(i) + "...." + s));
        while (actions_.size() <= i) {
            actions_.push_back(ActionFactory("NoAction"));
        }
        actions_[i] = ActionFactory(s);
        ++i;
    }
    items_.push_back(space + string("0....exit"));
}

void Menu::Paint() {
    cout << title_ << endl;
    for(const auto &s : items_) {
        cout << s << endl;
    }
    cout << "Choose(0-" << items_.size() - 1 << "): ";
}

void Menu::Run() {
    while(true) {   
        CLS
        Paint();
        string choose;
        getline(cin, choose);
        if(choose == "0") {
            break;
        }
        if(choose.empty()) {
            continue;
        }
        if(!ChooseCheck(choose)) {
            cout << "Choose Error!" << endl;
            cin.get();
            continue;
        }
        auto act = actions_[stoi(choose)];
        try {
            act->Run();
        }
        catch (runtime_error err) {
            cout << err.what() << endl;
        }
        cout << endl << "Press [Enter] to continue." << endl;
        cin.get();
    }
}

bool Menu::ChooseCheck(const string& choose) {
    return IsNum(choose) && stoi(choose) >= 0 && stoi(choose) <= items_.size();
}