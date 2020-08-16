// student.cpp
// Student related classes
// Han Li 29/6/2020

#include <cstring>
#include "../attana.h"

namespace ana {
// === Student ===

Student::Student(int stuID, const char *stuName, int puncherID)
: stuID(stuID), puncherID(puncherID) {
    strcpy(this->stuName, stuName);
}

// === StudentRecord ===

StudentRecord::StudentRecord(int stuID, const char *stuName, int puncherID)
: _stu(stuID, stuName, puncherID)
, stu(_stu) {}

// === StudentBlock ===

ResultsBlock::ResultsBlock(int count)
: _count(count)
, _daysInvolved(0)
, stuList(_stuList) {
    // reference allocation
    this->_ref = new int;
    *this->_ref = 1;
    this->_stuList = count == 0 ? NULL : new StudentRecord *[count];
}

ResultsBlock::ResultsBlock(const ResultsBlock& src)
: _count(src._count)
, _daysInvolved(src._daysInvolved)
, stuList(_stuList) {
    this->_ref = src._ref;
    (*this->_ref)++;
    this->_stuList = src._stuList;
}

ResultsBlock::~ResultsBlock() {
    if (--(*this->_ref) == 0) {
        // there's no reference of it, delete it
        delete [] this->_stuList;
        delete this->_ref;
    }
}

}