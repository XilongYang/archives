#include "judge.h"

bool IsNum(const string& str)
{
    for(auto c : str)
    {
        if(!isdigit(c))
        {
            return false;
        }
    }
    return true;
}