// utils.h
// utilities classes
// Han Li 28/6/2020

#ifndef utils_h
#define utils_h

#include <vector>
#include <date/date.h>

namespace ana {

enum Weekday {
    SUN, MON, TUE, WED, THU, FRI, SAT
};

static const char* WEEKDAY_STR[] = {
    "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"
};

typedef struct {
    int hr;
    int min;
} HourMin;

// Date class holds information of a date
class Date {
    static const Weekday wdays[];   // weekdays table
    date::year_month_day date;      // date encapsulation
    Weekday weekday_i;              // weekday
    
    static date::year_month_day parseDate(const char *dateStr);
public:
    inline const Weekday& weekday() const { return weekday_i; }
    const unsigned int dd, mm, yyyy;
    Date();
    Date(int dd, int mm, int yyyy);
    Date(const Date &another);
    // initialise a date with its 2020-06-28 form
    Date(const char *dateStr);
    
    // is before
    inline bool operator< (const Date& date) const {
        return this->date < date.date;
    }
    // is before or equal
    inline bool operator<= (const Date& date) const {
        return this->date <= date.date;
    }
    // is after
    inline bool operator> (const Date& date) const {
        return this->date > date.date;
    }
    // is after or equal
    inline bool operator>= (const Date& date) const {
        return this->date >= date.date;
    }
    // is equal
    inline bool operator== (const Date& date) const {
        return this->date == date.date;
    }
    // days in between
    inline int operator- (const Date& date) const {
        auto i = (date::sys_days)this->date - (date::sys_days)date.date;
        return i.count();
    }
    
};

// Moment class holds information of a moment
class Moment {
    Date _date;
    int _hr;
    int _min;
    int _sec;
public:
    
    inline int hr() { return _hr; };
    inline int min() { return _min; };
    inline int sec() { return _sec; };
    inline Date& date() { return _date; };
    // current moment
    Moment();
    // moment with exact hour, minute, second values of current day
    Moment(unsigned int hr, unsigned int min, unsigned int sec);
    // moment with exact hour, minute, second values and a date
    Moment(unsigned int hr, unsigned int min, unsigned int sec, unsigned int day, unsigned int month, unsigned int year);
    // moment parsed with 2020-06-29 as date string, 16:44:02 as time string
    Moment(const char *dateStr, const char *timeStr);
    
    // is before
    bool operator< (const Moment& date) const;
    // is before or equal
    bool operator<= (const Moment& date) const;
    // is before or equals to a time
    bool operator<= (const HourMin& date) const;
    // is after
    bool operator> (const Moment& date) const;
    // is after or equal
    bool operator>= (const Moment& date) const;
    // is after or equals to a time
    bool operator>= (const HourMin& date) const;
    // is equal
    bool operator== (Moment& date) const;
    
};

}

#endif /* utils_h */
