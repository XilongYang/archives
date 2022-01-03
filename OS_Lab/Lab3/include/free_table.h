#ifndef FREE_TABLE_H
#define FREE_TABLE_H

#include <vector>
#include "space.h"

using std::vector;

class FreeTable {
public:
    static FreeTable& GetInstance();
    Space Malloc(unsigned size);
    void Free(Space target);
    void Show();
private:
    FreeTable();
    FreeTable(const FreeTable&) = delete;
    FreeTable(FreeTable&&) = delete;
    vector<Space> table_;
    static FreeTable instance_;
    const static unsigned minestSize_;
};

#endif