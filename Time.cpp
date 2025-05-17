#include <iostream>
#include <iomanip>
#include "memtrace.h"
#include "Time.h"

bool Time::operator==(const Time& t) { //equal?
    if (t.min != min || t.hour != hour)
        return false;
    return true;
}

Time& Time::getTime(){ //getter
    return *this;
}

Time& Time::operator=(const Time& t) {
    hour = t.hour;
    min = t.min;
    return *this;
}
Time Time::operator+(int m){ //add minutes
    int hours = m / 60;
    m -= hours*60;
    if (m + min < 60)
        return Time(hour+hours , m + min);
    else
        return Time(hour + hours + 1 , m+min-60);
}

Time Time::operator+(const Time& t){//add another time
    int hours = t.hour;
    int m = t.min;
    if (m + min < 60)
        return Time(hour+hours , m + min);
    else
        return Time(hour + hours + 1 , m+min-60);
}

Time Time::operator-(int m){ //decrease by minutes
    int hours = m / 60;
    m -= hours*60;
    if (min-m >= 0)
        return Time(hour-hours , min-m);
    else
        return Time(hour - hours - 1 , min-m+60);
}

Time Time::operator-(const Time& t){//decrease by another time
    int hours = t.hour;
    int m = t.min;
    if (min-m >= 0)
        return Time(hour-hours , min-m);
    else
        return Time(hour - hours - 1 , min-m+60);
}

void Time::print(std::ostream& os) {
    os << std::setw(2) << std::setfill('0') << hour << "::" << std::setw(2) << min;
}

bool Time::operator>=(const Time& t){
    if(*this == t)
        return true;
    if((hour == t.hour && min >= t.min) || (hour > t.hour))
        return true;
    return false;
}

Time::~Time() { //dtor
    hour = 0;
    min = 0;
}
