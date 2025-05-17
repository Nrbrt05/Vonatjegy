#include <iostream>
#include <iomanip>
#include "memtrace.h"
#include "Date.h"

void Date::print(std::ostream& os) { //kiirja a datumot
    os << std::setw(4) << std::setfill('0') << yr << "." << std::setw(2) << month << "." << std::setw(2)<< day;
}
bool Date::operator==(Date& d){
    if (d.day != day || d.month != month || d.yr != yr)
        return false;
    return true;
}
Date::~Date() {
yr = 0; month = 0; day = 0;
}

Date& Date::operator=(const Date& d){
    yr = d.yr;
    month = d.month;
    day = d.day;
    return *this;
}
