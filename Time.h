#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <iomanip>
#include "memtrace.h"
#include "string5.h"

class Time {
    int hour;
    int min;
public:
    Time(int h = 0 , int m = 0) :hour(h) , min(m) {};
    Time(const Time& t) :hour(t.hour) , min(t.min) {};
    bool operator==(const Time& t);
    Time& getTime();
    Time& operator=(const Time& t);
    Time operator+(int m);
    Time operator+(const Time& t);
    Time operator-(int m);
    Time operator-(const Time& t);
    void print(std::ostream& os);
    bool operator>=(const Time& t);
    ~Time();
};
#endif
