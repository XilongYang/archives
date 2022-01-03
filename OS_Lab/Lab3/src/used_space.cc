#include "used_space.h"

UsedSpace::UsedSpace(const string& name, const Space& space)
    : name_(name), Space(space) {}

string UsedSpace::GetName() const {
    return name_;
}

void UsedSpace::SetName(const string& name) {
    name_ = name;
}
