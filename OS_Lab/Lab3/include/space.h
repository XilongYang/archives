#ifndef SPACE_H
#define SPACE_H

class Space {
public:
    Space(unsigned size, unsigned startPos, bool status);
    unsigned GetSize() const;
    unsigned GetStartPos() const;
    bool GetStatus() const;
    void SetSize(unsigned size);
    void SetStartPos(unsigned startPos);
    void SetStatus(bool status);
private:
    unsigned size_;
    unsigned startPos_;
    bool status_;
};

#endif