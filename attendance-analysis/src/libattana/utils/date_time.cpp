// date_time.cpp
// handle dates and times
// Han Li 29/6/2020

#include <cstring>
#include "../utils.h"

using namespace date;
using namespace std::chrono;

namespace ana {

Weekday const Date::wdays[] = {
    SUN, MON, TUE, WED, THU, FRI, SAT
};


// initialise a date with current system time
Date::Date():
date(year_month_day{floor<days>(system_clock::now())}),
weekday_i(wdays[date::weekday{date}.c_encoding()]),
dd(date.day()), mm(date.month()), yyyy((int)date.year())
{}

// initialise a date with dd/mm/yyyy format
Date::Date(int dd, int mm, int yyyy):
date(year{yyyy}/mm/dd),
weekday_i(wdays[date::weekday{date}.c_encoding()]),
dd(date.day()), mm(date.month()), yyyy((int)date.year()) {
    // invalid date
    if (!date.ok()) {
        date = year{1970}/1/1;
    }
}

Date::Date(const Date &another)
: date(year{(int)another.yyyy}/another.mm/another.dd)
, weekday_i(wdays[date::weekday{date}.c_encoding()])
, dd(date.day()), mm(date.month()), yyyy((int)date.year()) {
    // invalid date
    if (!date.ok()) {
        date = year{1970}/1/1;
    }
}

date::year_month_day Date::parseDate(const char *dateStr) {
    int y1, y2, y3;
    sscanf(dateStr, "%d-%d-%d", &y1, &y2, &y3);
    date::year_month_day date = year_month_day(year{y1}/y2/y3);
    if (!date.ok()) {
        date = year{1970}/1/1;
    }
    return date;
}

Date::Date(const char *dateStr)
: date(Date::parseDate(dateStr))
, dd(date.day()), mm(date.month()), yyyy((int)date.year()) {
    int y1, y2, y3;
    sscanf(dateStr, "%d-%d-%d", &y1, &y2, &y3);
    this->date = year_month_day(year{y1}/y2/y3);
    if (!date.ok()) {
        date = year{1970}/1/1;
    }
    
    weekday_i = wdays[date::weekday{date}.c_encoding()];
}

Moment::Moment() {
    system_clock::time_point tp = system_clock::now();
    auto dp = floor<days>(tp);
    auto time = make_time(tp-dp);
    _hr = (int)time.hours().count();
    _min = (int)time.minutes().count();
    _sec = (int)time.seconds().count();
}

Moment::Moment(unsigned int hr, unsigned int min, unsigned int sec) {
    _hr = hr > 23 ? 0 : hr;
    _min = min > 59 ? 0 : min;
    _sec = sec > 59 ? 0 : sec;
}

Moment::Moment(unsigned int hr, unsigned int min, unsigned int sec, unsigned int day, unsigned int month, unsigned int year)
: _date(day, month, year) {
    _hr = hr > 23 ? 0 : hr;
    _min = min > 59 ? 0 : min;
    _sec = sec > 59 ? 0 : sec;
}

Moment::Moment(const char *dateStr, const char *timeStr)
: _date(dateStr) {
    // 1. parse date (done in initialise list)
    // 2. parse time
    sscanf(timeStr, "%d:%d:%d", &_hr, &_min, &_sec);
}

// is before
bool Moment::operator< (const Moment& date) const {
    if (this->_date == date._date) {
        if (this->_hr < date._hr) {
            return true;
        } else if (this->_hr == date._hr && this->_min < date._min) {
            return true;
        } else if (this->_hr == date._hr && this->_min == date._min && this->_sec < date._sec) {
            return true;
        } else {
            return false;
        }
    } else {
        return this->_date < date._date;
    }
}
// is before or equal
bool Moment::operator<= (const Moment& date) const {
    if (this->_date == date._date) {
        if (this->_hr < date._hr) {
            return true;
        } else if (this->_hr == date._hr && this->_min < date._min) {
            return true;
        } else if (this->_hr == date._hr && this->_min == date._min && this->_sec < date._sec) {
            return true;
        } else if (this->_hr == date._hr && this->_min == date._min && this->_sec == date._sec) { // <=
            return true;
        } else {
            return false;
        }
    } else {
        return this->_date < date._date;
    }
}
// is before or equals to a time
bool Moment::operator<= (const HourMin& date) const {
    if (this->_hr < date.hr) {
        return true;
    } else if (this->_hr == date.hr && this->_min < date.min) {
        return true;
    }  else if (this->_hr == date.hr && this->_min == date.min) { // <=
        return true;
    } else {
        return false;
    }
}


// is after
bool Moment::operator> (const Moment& date) const {
    if (this->_date == date._date) {
        if (this->_hr > date._hr) {
            return true;
        } else if (this->_hr == date._hr && this->_min > date._min) {
            return true;
        } else if (this->_hr == date._hr && this->_min == date._min && this->_sec > date._sec) {
            return true;
        } else {
            return false;
        }
    } else {
        return this->_date > date._date;
    }
}
// is after or equal
bool Moment::operator>= (const Moment& date) const {
    if (this->_date == date._date) {
        if (this->_hr > date._hr) {
            return true;
        } else if (this->_hr == date._hr && this->_min > date._min) {
            return true;
        } else if (this->_hr == date._hr && this->_min == date._min && this->_sec > date._sec) {
            return true;
        } else if (this->_hr == date._hr && this->_min == date._min && this->_sec == date._sec) { // >=
            return true;
        } else {
            return false;
        }
    } else {
        return this->_date > date._date;
    }
}

// is before or equals to a time
bool Moment::operator>= (const HourMin& date) const {
    if (this->_hr > date.hr) {
        return true;
    } else if (this->_hr == date.hr && this->_min > date.min) {
        return true;
    }  else if (this->_hr == date.hr && this->_min == date.min) { // >=
        return true;
    } else {
        return false;
    }
}


// is equal
bool Moment::operator== (Moment& date) const {
    return this->_date == date._date &&
    this->_hr == date._hr &&
    this->_min == date._min &&
    this->_sec == date._sec;
}

}