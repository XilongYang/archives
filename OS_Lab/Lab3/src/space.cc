#include "space.h"

Space::Space(unsigned size, unsigned startPos, bool status)
    : size_(size), startPos_(startPos), status_(status) {}

unsigned Space::GetSize() const {
    return size_;
}

unsigned Space::GetStartPos() const {
    return startPos_;
}

bool Space::GetStatus() const {
    return status_;
}

void Space::SetSize(unsigned size) {
    size_ = size;
}

void Space::SetStartPos(unsigned startPos) {
    startPos_ = startPos;
}

void Space::SetStatus(bool status) {
    status_ = status;
}
