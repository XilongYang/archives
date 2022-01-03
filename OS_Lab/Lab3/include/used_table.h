#ifndef USED_TABLE_H
#define USED_TABLE_H

#include <vector>
#include <string>
#include "used_space.h"

using std::vector;

class UsedTable {
public:
    static UsedTable& GetInstance();
    void Malloc(UsedSpace space);
    Space Free  (const string& name);
    void Show();
private:
    UsedTable() = default;
    UsedTable(const UsedTable&) = delete;
    UsedTable(UsedTable&&) = delete;
    vector<UsedSpace> table_; 
    static UsedTable instance_;
};

#endif