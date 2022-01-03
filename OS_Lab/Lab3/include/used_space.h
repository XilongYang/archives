#ifndef USED_SPACE_H
#define USED_SPACE_H

#include <string>
#include "space.h"

using std::string;

class UsedSpace : public Space{
public:
    UsedSpace(const string& name, const Space& space);
    string GetName() const;
    void SetName(const string& name);
private:
    string name_;
};

#endif