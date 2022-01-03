#include "used_table.h"
#include <iostream>
#include <iomanip>

using std::runtime_error;
using std::cout;
using std::endl;
using std::setw;

UsedTable UsedTable::instance_;

UsedTable& UsedTable::GetInstance() {
    return instance_;
}

void UsedTable::Malloc(UsedSpace space) {
    table_.push_back(space);
}

Space UsedTable::Free(const string& name) {
    for(auto i = table_.begin(); i != table_.end(); ++i) {
        if(i->GetName() == name) {
            Space s = *i;
            table_.erase(i);
            return s;
        }
    }
    throw runtime_error("No space found");
}

void UsedTable::Show() {
    cout << setw(10) << "Name" << setw(10) << "StartPos" << setw(10) << "Size" 
    << setw(10) << "Status" << endl;
    for(int i = 0; i < table_.size(); ++i) {
        cout << setw(10) << table_[i].GetName() 
        << setw(10) << table_[i].GetStartPos() 
        << setw(10) << table_[i].GetSize()
        << setw(10) << table_[i].GetStatus() << endl;
    }
}
