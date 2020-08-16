// attana.h
// main classes
// Han Li 29/6/2020

#ifndef attana_h
#define attana_h

#ifdef _WIN32
#define BUILDING_DLL 1
#endif
#include <libattana.h>
#include "utils.h"

namespace ana {
// PunchRecord class holds
class PunchRecord {
    StudentRecord* _stuRec;     // the corresponding student
    Moment _punchTime;          // the time at which the student punched in
    
public:
    inline StudentRecord* stuRec() { return _stuRec; }
    inline Moment & punchTime() { return _punchTime; }
    PunchRecord(StudentRecord* stuRec, Moment& punchTime);
};

// Analyser class holds information of a series of students and their attendance information
class Analyser {
    friend inline bool readPunchList(Analyser& , const char *);
    friend inline bool readStuList(Analyser& , const char *);
    
    std::vector<StudentRecord *> list;      // the student's list
    std::vector<PunchRecord *> punches;     // the punch in record list
    
    // default values
    const HourMin defInStart;
    const HourMin defInEnd;
    const HourMin defOutStart;
    const HourMin defOutEnd;
    const Date defStartDate;
    const Date defEndDate;
    
    // methods
    bool readStuList(const char *);
    bool readPunchList(const char *);
public:
    Analyser(const HourMin& tInS, const HourMin& tInE, const HourMin& tOutS, const HourMin& tOutE, const Date& defStartD, const Date& defEndD);
    ~Analyser();
    // read all
    bool readLists(const char *stuListFile, const char *attListFile);
    
    // gets a student object through its student ID, NULL if not found
    ResultsBlock get(int stuID);
    // select student(s) by name
    ResultsBlock get(const char *name);
    // select student(s) between two certain dates
    ResultsBlock get(const Date& dateLeft, const Date& dateRight);
    // ·select student(s) from a certain weekday
    ResultsBlock get(const Weekday weekday);
    // TODO - select student(s) whose attendant rate is bigger (less) than (eq. to) [rate]%. default: less, not equal
    ResultsBlock get(double rate, bool bigger = false, bool equal = false);
    // TODO - select student(s) whose attendant rate is between (or equal) two values ([rate]%). default: left - not equal; right - not equal
    ResultsBlock get(double lrate, double rrate, bool lequal = false, bool requal = false);
};

}

#endif /* attana_h */
