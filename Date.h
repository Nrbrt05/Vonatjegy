#ifndef DATE_H
#define DATE_H
#include <iomanip>
#include <iostream>
#include "memtrace.h"
class Date {
    int yr;
    int month;
    int day;
public:
    Date(int y = 0 , int m = 0 , int d = 0) :yr(y) , month(m) , day(d) {};
    void print(std::ostream& os);
    Date& operator=(const Date& d);
    bool operator==(Date& d);
    ~Date();
};
#endif
