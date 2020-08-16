// libattana.h
// Attendancy Analyser library header
// Han Li 28/6/2020

#ifndef libattana_h
#define libattana_h

#ifdef USING_DLL
#define DLLPORT _declspec(dllimport)
#elif BUILDING_DLL
#define DLLPORT _declspec(dllexport)
#else
#define DLLPORT
#endif

namespace ana {
// Student class holds information of a student
class DLLPORT Student {
    friend class StudentRecord;
    int stuID;          // student ID
    char stuName[20];   // student's name
    int puncherID;      // the corresponding puncher's ID
    
    Student(int stuID, const char *stuName, int puncherID);
public:
    inline int getStuID() const { return this->stuID; }
    inline const char* getStuName() const { return this->stuName; }
    inline int getPuncherID() const { return this->puncherID; }
};

// StudentRecord class holds information of a student and his/her attendance info
class DLLPORT StudentRecord {
    friend class Analyser;
    Student _stu;
    int attendCount;        // count of attend(s);
    int absentCount;        // count of absence from school;
    int lateCount;          // count of being late;
    int earlyLeaveCount;    // count of early-leaves;
    
    StudentRecord(int stuID, const char *stuName, int puncherID);
public:
    const Student & stu;
    int inFlag; // inFlag = [dayRound] represents the student has a valid punch-in record during the day
    int outFlag; // outFlag = [dayRound] represents the student has a valid punch-out record during the day
    inline bool hasPuncherID(int puncherID) { return this->_stu.puncherID == puncherID; }
    inline bool hasName(const char* name) { return 0 == strcmp(this->_stu.stuName, name); }
    inline void increaseAttend() { ++attendCount; }
    inline int attend() { return attendCount; }
    inline void increaseAbsent() { ++absentCount; }
    inline int absent() { return absentCount; }
    inline void increaseLate() {  ++lateCount; }
    inline int late() { return lateCount; }
    inline void increaseEarlyLeave() { ++earlyLeaveCount; }
    inline int earlyLeave() { return earlyLeaveCount; }
    inline void purgeRecords() {
        inFlag = outFlag = attendCount = absentCount = lateCount = earlyLeaveCount = 0;
    }
};

// StudentBlock class simply holds a series of student, typically used as select results
class DLLPORT ResultsBlock {
    friend class Analyser;
    int* _ref;                  // references count, can "delete" if reaches 0
    StudentRecord** _stuList;   // NULL if it is a void block;
    int _count;                 // block size
    int _daysInvolved;          // days that involved in the counting
public:
    inline int count() const { return _count; };
    inline int daysInvolved() const { return _daysInvolved; };
    StudentRecord** const& stuList;
    ResultsBlock(int count);
    ResultsBlock(const ResultsBlock& src);
    ~ResultsBlock();
};

class Analyser;

class DLLPORT Selector {
    Analyser* ana;
    bool isOK;
public:
    Selector(const char *);
    Selector();
    ~Selector();
    
    ResultsBlock select(const char *expression);
    inline bool operator!() { return !isOK; }
};

}

#endif /* libattana_h */
