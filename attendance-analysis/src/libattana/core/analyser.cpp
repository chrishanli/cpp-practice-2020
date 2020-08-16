// analyser.cpp
// PunchRecord class and Analyser class

#include <fstream>
#include <cstring>
#include <vector>
#include <set>
#include "../attana.h"

namespace ana {
// === PunchRecord class ===

PunchRecord::PunchRecord(StudentRecord* stuRec, Moment& punchTime)
: _stuRec(stuRec)
, _punchTime(punchTime) {}

// === Analyser class ===

Analyser::Analyser(const HourMin& tInS, const HourMin& tInE, const HourMin& tOutS, const HourMin& tOutE, const Date& defStartD, const Date& defEndD)
: defInStart(tInS), defInEnd(tInE), defOutStart(tOutS), defOutEnd(tOutE)
, defStartDate(defStartD), defEndDate(defEndD) {}

Analyser::~Analyser() {
    // iterate through two vectors and destroy them
    std::vector<StudentRecord *>::iterator iStudent;
    std::vector<PunchRecord *>::iterator iPunch;
    
    for (iStudent = this->list.begin();
         iStudent != this->list.end(); ++iStudent) {
        delete *iStudent;
    }
    for (iPunch = this->punches.begin();
         iPunch != this->punches.end(); ++iPunch) {
        delete *iPunch;
    }
}

inline void parseStudent(const char *in, int *serial, int *stuID, char *name, int *puncherID) {
    std::istringstream is(in);
    static char buffer[80];
    is.getline(buffer, 80, ',');
    *serial = atoi(buffer);
    is.getline(buffer, 80, ',');
    *stuID = atoi(buffer);
    is.getline(name, 80, ',');
    is.getline(buffer, 80);
    *puncherID = atoi(buffer);
}

bool Analyser::readStuList(const char *stuListFile) {
    // 1. open the input file
    std::ifstream inFile(stuListFile);
    if (!inFile) {
        return false;
    }
    // 2. try to get the lines, one by one
    char inBuff[100], nameBuff[20];
    int serial, stuID, puncherID;
    
    inFile.getline(inBuff, 100); // except for the title line
    
    while (!inFile.eof()) {
        inFile.getline(inBuff, 100);
        // 3. parse
        parseStudent(inBuff, &serial, &stuID, nameBuff, &puncherID);
        
        // 4. make an object and save
        this->list.push_back(new StudentRecord(stuID, nameBuff, puncherID));
    }
    inFile.close();
    
    return true;
}


inline void parsePunch(const char *in, int *puncherID, char dateStr[], char timeStr[]) {
    sscanf(in, "%d%s%s", puncherID, dateStr, timeStr);
}

inline StudentRecord* findStuByPuncherID(std::vector<StudentRecord *>& stuList, int puncherID) {
    // sorry, no time for indexing! search throughly instead
    std::vector<StudentRecord *>::iterator i;
    for (i = stuList.begin(); i != stuList.end(); ++i) {
        if ((*i)->hasPuncherID(puncherID)) {
            return *i;
        }
    }
    return NULL;
}

inline bool isBetween(Moment& time, HourMin& startTime, HourMin& endTime) {
    return time >= startTime && time <= endTime;
}

inline void analysePunchRecord(PunchRecord* pr, const HourMin& InStartTime, const HourMin& InEndTime, const HourMin& OutStartTime, const HourMin& OutEndTime, int flagFiller) {
    // judge if the student is "attend"
    if (pr->punchTime() >= InStartTime && pr->punchTime() <= InEndTime) {
        // valid punch-in, record
        pr->stuRec()->inFlag = flagFiller;
    } else if (pr->punchTime() >= OutStartTime && pr->punchTime() <= OutEndTime) {
        // valid punch-out, record
        pr->stuRec()->outFlag = flagFiller;
    } // other cases not record, so valid record will only be recorded as one
}

inline void analyseOneStudentThisDay(StudentRecord *stu, int flagFiller) {
    if (stu->inFlag == flagFiller) {
        if (stu->outFlag == flagFiller) {
            // (1) valid in and out, attend
            stu->increaseAttend();
        } else {
            // (2) valid in but invalid out, early-leave
            stu->increaseEarlyLeave();
        }
    } else {
        if (stu->outFlag == flagFiller) {
            // (3) invalid in but valid out, late
            stu->increaseLate();
        } else {
            // (3) invalid in and invalid out, absent
            stu->increaseAbsent();
        }
    }
}

inline void analyseAllStudentThisDay(std::vector<StudentRecord *>& stuList, int flagFiller) {
    std::vector<StudentRecord *>::iterator stui;
    for (stui = stuList.begin(); stui != stuList.end(); ++stui) {
        analyseOneStudentThisDay(*stui, flagFiller);
    }
}


bool Analyser::readPunchList(const char *attListFile) {
    // 1. open the input file
    std::ifstream inFile(attListFile);
    if (!inFile) {
        return false;
    }
    // 2. try to get the lines, one by one
    char lineBuff[100], dateBuff[20], timeBuff[20];
    int puncherID;
    StudentRecord* corrsStu;
    while (!inFile.eof()) {
        // 2.1 try to get the line
        inFile.getline(lineBuff, 100);
        // 2.2. parse
        parsePunch(lineBuff, &puncherID, dateBuff, timeBuff);
        Moment mom(dateBuff, timeBuff);
        // 2.3. find corresponding student
        corrsStu = findStuByPuncherID(this->list, puncherID);
        if (corrsStu) {
            // 2.4 make an object and save
            this->punches.push_back(new PunchRecord(corrsStu, mom));
        }
    }
    return true;
}

bool Analyser::readLists(const char *stuListFile, const char *attListFile) {
    return readStuList(stuListFile) && readPunchList(attListFile);
}


// select student by id
ResultsBlock Analyser::get(int stuID) {
    std::vector<StudentRecord *>::iterator i;
    StudentRecord *result = NULL;
    
    // 1. find the student
    for (i = this->list.begin(); i != this->list.end(); i++) {
        if ((*i)->stu.getStuID() == stuID) {
            result = *i;
            break;
        }
    }
    
    // 2. judge if the student was found
    if (!result) {
        ResultsBlock sb(0);
        return sb;
    }
    
    // 3. analyse the student (default date & time period)
    std::vector<PunchRecord *>::iterator ip = this->punches.begin();
    
    // 3.0 jump to the default begin date
    while ((*ip)->punchTime().date() < defStartDate && ip != this->punches.end()) {
        ip++;
    }
    if (ip == this->punches.end()) {
        // weird start date
        ResultsBlock sb(0);
        return sb;
    }
    
    int fill = (*ip)->punchTime().date().dd;
    result->purgeRecords();
    
    ResultsBlock sb(1);
    while (ip != this->punches.end() && (*ip)->punchTime().date() <= defEndDate) {
        // jump if it is saturday / sunday
        if ((*ip)->punchTime().date().weekday() == SAT || (*ip)->punchTime().date().weekday() == SUN) {
            fill = ip == this->punches.end() ? 0 : (*ip)->punchTime().date().dd;
            continue;
        }
        
        // 3.1 search the student's record within the day
        while (ip != this->punches.end() && (*ip)->punchTime().date().dd == fill) {
            // 3.1.1 check if the student is correspond
            if ((*ip)->stuRec() != result) {
                ip++; continue;
            }
            // 3.1.2 analyse the student's record
            analysePunchRecord(*ip, defInStart, defInEnd, defOutStart, defOutEnd, fill);
            // 3.1.3 go to the next record
            ip++;
        }
        // 3.2 analyse the student within the day
        analyseOneStudentThisDay(result, fill);
        sb._daysInvolved++;
        // 3.3 change the flag filler
        fill = ip == this->punches.end() ? 0 : (*ip)->punchTime().date().dd;
    }
    
    // 4. return
    sb.stuList[0] = result;
    
    return sb;
}

// select student(s) by name
ResultsBlock Analyser::get(const char *name) {
    std::vector<StudentRecord *>::iterator i;
    StudentRecord *result = NULL;
    
    // 1. find the student
    for (i = this->list.begin(); i != this->list.end(); i++) {
        if ((*i)->hasName(name)) {
            result = *i;
            break;
        }
    }
    
    // 2. judge if the student was found
    if (!result) {
        ResultsBlock sb(0);
        return sb;
    }
    
    // 3. analyse the student (default date & time period)
    std::vector<PunchRecord *>::iterator ip = this->punches.begin();
    
    // 3.0 jump to the default begin date
    while ((*ip)->punchTime().date() < defStartDate && ip != this->punches.end()) {
        ip++;
    }
    if (ip == this->punches.end()) {
        // weird start date
        ResultsBlock sb(0);
        return sb;
    }
    
    int fill = (*ip)->punchTime().date().dd;
    result->purgeRecords();
    
    ResultsBlock sb(1);
    while (ip != this->punches.end() && (*ip)->punchTime().date() <= defEndDate) {
        // jump if it is saturday / sunday
        if ((*ip)->punchTime().date().weekday() == SAT || (*ip)->punchTime().date().weekday() == SUN) {
            fill = ip == this->punches.end() ? 0 : (*ip)->punchTime().date().dd;
            continue;
        }
        
        // 3.1 search the student's record within the day
        while (ip != this->punches.end() && (*ip)->punchTime().date().dd == fill) {
            // 3.1.1 check if the student is correspond
            if ((*ip)->stuRec() != result) {
                ip++; continue;
            }
            // 3.1.2 analyse the student's record
            analysePunchRecord(*ip, defInStart, defInEnd, defOutStart, defOutEnd, fill);
            // 3.1.3 go to the next record
            ip++;
        }
        // 3.2 analyse the student within the day
        analyseOneStudentThisDay(result, fill);
        sb._daysInvolved++;
        // 3.3 change the flag filler
        fill = ip == this->punches.end() ? 0 : (*ip)->punchTime().date().dd;
    }
    
    // 4. return
    sb.stuList[0] = result;
    
    return sb;
}

// select student(s) between two certain dates
ResultsBlock Analyser::get(const Date& dateLeft, const Date& dateRight) {
    // 1. jump to the date
    std::vector<PunchRecord *>::iterator ip = this->punches.begin();
    while (ip != this->punches.end() && (*ip)->punchTime().date() < dateLeft) {
        ip++;
    }
    if (ip == this->punches.end() || !((*ip)->punchTime().date() == dateLeft)) {
        // weird date
        ResultsBlock sb(0);
        return sb;
    }
    
    // 2. analyse
    int fill = 0;
    // 2.0 purge all students, prepare for result
    ResultsBlock sb((int)this->list.size());
    std::vector<StudentRecord *>::iterator is = this->list.begin();
    while (is != this->list.end()) {
        (*is)->purgeRecords();
        sb.stuList[fill++] = *(is++);
    }
    
    fill = (*ip)->punchTime().date().dd;
    while (ip != this->punches.end() && (*ip)->punchTime().date() <= dateRight) {
        // jump if it is saturday / sunday
        if ((*ip)->punchTime().date().weekday() == SAT || (*ip)->punchTime().date().weekday() == SUN) {
            fill = ip == this->punches.end() ? 0 : (*ip)->punchTime().date().dd;
            continue;
        }
        
        // 2.1 search within the day
        while (ip != this->punches.end() && (*ip)->punchTime().date().dd == fill) {
            // 2.1.1 analyse the student's record
            analysePunchRecord(*ip, defInStart, defInEnd, defOutStart, defOutEnd, fill);
            
            // 2.1.3 go ahead to the next record
            ip++;
        }
        
        // 2.2 analyse today's records
        analyseAllStudentThisDay(this->list, fill);
        sb._daysInvolved++;
        
        // 2.3 update flagFiller
        fill = ip == this->punches.end() ? 0 : (*ip)->punchTime().date().dd;
    }
    
    // 3. return
    return sb;
}

// select student(s) from a certain weekday
ResultsBlock Analyser::get(Weekday weekday) {
    // jump if it is saturday/sunday
    if (weekday == SAT || weekday == SUN) {
        ResultsBlock sb(0);
        return sb;
    }
    
    // 1. jump to the default start date
    std::vector<PunchRecord *>::iterator ip = this->punches.begin();
    while (ip != this->punches.end() && (*ip)->punchTime().date() < defStartDate) {
        ip++;
    }
    if (ip == this->punches.end() || !((*ip)->punchTime().date() == defStartDate)) {
        // weird date
        ResultsBlock sb(0);
        return sb;
    }
    
    // 2. analyse
    int fill = 0;
    // 2.0 purge all students, prepare for result
    ResultsBlock sb((int)this->list.size());
    std::vector<StudentRecord *>::iterator is = this->list.begin();
    while (is != this->list.end()) {
        (*is)->purgeRecords();
        sb.stuList[fill++] = *(is++);
    }
    
    fill = (*ip)->punchTime().date().dd;
    while (ip != this->punches.end() && (*ip)->punchTime().date() <= defEndDate) {
        // 2.1 check if the weekday is correspond
        if ((*ip)->punchTime().date().weekday() != weekday) {
            // jump to next day, if not
            while (ip != this->punches.end() && (*ip)->punchTime().date().dd == fill) {
                ip++;
            }
            fill = ip == this->punches.end() ? 0 : (*ip)->punchTime().date().dd;
            continue;
        }
        
        // 2.2 search within the day
        while (ip != this->punches.end() && (*ip)->punchTime().date().dd == fill) {
            // 2.2.1 analyse the student's record
            analysePunchRecord(*ip, defInStart, defInEnd, defOutStart, defOutEnd, fill);
            
            // 2.2.2 go ahead to the next record
            ip++;
        }
        
        // 2.3 analyse today's records
        analyseAllStudentThisDay(this->list, fill);
        sb._daysInvolved++;
        
        // 2.4 update flagFiller
        fill = ip == this->punches.end() ? 0 : (*ip)->punchTime().date().dd;
    }
    
    // 3. return
    return sb;
}

// select student(s) whose attendant rate is bigger (less) than (eq. to) [rate]%.
// default: less, not equal (<)
ResultsBlock Analyser::get(double rate, bool bigger, bool equal) {
    // 1. jump to the default start date
    std::vector<PunchRecord *>::iterator ip = this->punches.begin();
    while (ip != this->punches.end() && (*ip)->punchTime().date() < defStartDate) {
        ip++;
    }
    if (ip == this->punches.end() || !((*ip)->punchTime().date() == defStartDate)) {
        // weird date
        ResultsBlock sb(0);
        return sb;
    }
    
    // 2. select all students
    ResultsBlock sr(get(defStartDate, defEndDate)); int i;
    
    // 3. select students that satisfying the conditions
    
    std::vector<StudentRecord *> satisfying;
    if (bigger && equal) { // >=
        for (i = 0; i < sr.count(); ++i) {
            if (sr.stuList[i]->attend() / (double) sr._daysInvolved >= rate) {
                satisfying.push_back(sr.stuList[i]);
            }
        }
    } else if (bigger) { // >
        for (i = 0; i < sr.count(); ++i) {
            if (sr.stuList[i]->attend() / (double) sr._daysInvolved > rate) {
                satisfying.push_back(sr.stuList[i]);
            }
        }
    } else if (equal) { // <=
        for (i = 0; i < sr.count(); ++i) {
            if (sr.stuList[i]->attend() / (double) sr._daysInvolved <= rate) {
                satisfying.push_back(sr.stuList[i]);
            }
        }
    } else { // <
        for (i = 0; i < sr.count(); ++i) {
            if (sr.stuList[i]->attend() / (double) sr._daysInvolved < rate) {
                satisfying.push_back(sr.stuList[i]);
            }
        }
    }
    
    
    // 4. prepare for return
    ResultsBlock ret((int)satisfying.size());
    ret._daysInvolved = sr._daysInvolved; // necessary
    std::vector<StudentRecord *>::iterator satI;
    for (satI = satisfying.begin(), i = 0; satI != satisfying.end(); ++satI, ++i) {
        ret.stuList[i] = *satI;
    }
    
    return ret;
}

// select student(s) whose attendant rate is between (or equal) two values ([rate]%). default: left - not equal; right - not equal
ResultsBlock Analyser::get(double lrate, double rrate, bool lequal, bool requal) {
    // 1. jump to the default start date
    std::vector<PunchRecord *>::iterator ip = this->punches.begin();
    while (ip != this->punches.end() && (*ip)->punchTime().date() < defStartDate) {
        ip++;
    }
    if (ip == this->punches.end() || !((*ip)->punchTime().date() == defStartDate)) {
        // weird date
        ResultsBlock sb(0);
        return sb;
    }
    
    // 2. select all students
    ResultsBlock sr(get(defStartDate, defEndDate)); int i;
    
    // 3. select students that satisfying the conditions
    
    std::vector<StudentRecord *> satisfying;
    double rate;
    if (lequal && requal) { // >= l && <= r
        for (i = 0; i < sr.count(); ++i) {
            rate = sr.stuList[i]->attend() / (double) sr._daysInvolved;
            if (rate >= lrate && rate <= rrate) {
                satisfying.push_back(sr.stuList[i]);
            }
        }
    } else if (lequal) { // >= l && < r
        for (i = 0; i < sr.count(); ++i) {
            rate = sr.stuList[i]->attend() / (double) sr._daysInvolved;
            if (rate >= lrate && rate < rrate) {
                satisfying.push_back(sr.stuList[i]);
            }
        }
    } else if (requal) { // > l && <= r
        for (i = 0; i < sr.count(); ++i) {
            rate = sr.stuList[i]->attend() / (double) sr._daysInvolved;
            if (rate > lrate && rate <= rrate) {
                satisfying.push_back(sr.stuList[i]);
            }
        }
    } else { // > l && < r
        for (i = 0; i < sr.count(); ++i) {
            rate = sr.stuList[i]->attend() / (double) sr._daysInvolved;
            if (rate > lrate && rate < rrate) {
                satisfying.push_back(sr.stuList[i]);
            }
        }
    }
    
    
    // 4. prepare for return
    ResultsBlock ret((int)satisfying.size());
    ret._daysInvolved = sr._daysInvolved;
    std::vector<StudentRecord *>::iterator satI;
    for (satI = satisfying.begin(), i = 0; satI != satisfying.end(); ++satI, ++i) {
        ret.stuList[i] = *satI;
    }
    
    return ret;
}

}
