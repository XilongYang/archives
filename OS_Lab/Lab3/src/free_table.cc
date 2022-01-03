#include <iostream>
#include <iomanip>
#include "free_table.h"

using std::runtime_error;
using std::cout;
using std::endl;
using std::setw;

FreeTable FreeTable::instance_;
const unsigned FreeTable::minestSize_ = 1024;

FreeTable::FreeTable() {
    table_.push_back(Space(102400, 0, 1));
}

FreeTable& FreeTable::GetInstance() {
    return instance_;
}

Space FreeTable::Malloc(unsigned size) {
    if(size < minestSize_) {
        size = minestSize_;
    }
    for(auto i = table_.begin(); i != table_.end(); ++i) {
        if(i->GetSize() < minestSize_ || i->GetSize() < size) {
            continue;
        }
        if(i->GetSize() - size < minestSize_) {
            unsigned startPos = i->GetStartPos();
            table_.erase(i);
            return Space(size, startPos, 1);
        } else {
            unsigned startPos = i->GetStartPos() + i->GetSize() - size;
            i->SetSize(i->GetSize() - size);
            return Space(size, startPos, 1);
        }
    }
    throw runtime_error("Out of space");
}

void FreeTable::Free(Space target) {
    auto curPos = table_.end();
    for(auto i = table_.begin(); i != table_.end(); ++i) {
        if(i->GetStartPos() > target.GetStartPos()) {
            curPos = table_.insert(i, target);
            break;
        } else if(i == table_.end() - 1) {
            table_.push_back(target);
            curPos = table_.end() - 1;
            break;
        }
    }
    auto merge = [](vector<Space>&table, 
    vector<Space>::iterator pre, vector<Space>::iterator cur) 
    -> vector<Space>::iterator {
        if(cur == table.begin() || cur == table.end() || cur - pre != 1) {
            return cur;
        }
        if(pre->GetStartPos() + pre->GetSize() == cur->GetStartPos()) {
            pre->SetSize(pre->GetSize() + cur->GetSize());
            table.erase(cur);
            return pre;
        }
        return cur;
    };
    curPos = merge(table_, curPos - 1, curPos);
    curPos = merge(table_, curPos, curPos + 1);
}

void FreeTable::Show() {
    cout << setw(5) << "No." << setw(10) << "StartPos" << setw(10) << "Size" 
    << setw(10) << "Status" << endl;
    for(int i = 0; i < table_.size(); ++i) {
        cout << setw(5) << i + 1 << setw(10) << table_[i].GetStartPos() 
        << setw(10) << table_[i].GetSize()
        << setw(10) << table_[i].GetStatus() << endl;
    }
}
