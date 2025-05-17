#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <iomanip>
#include "memtrace.h"
#include "string5.h"
#include "Date.h"
#include "Time.h"
#include "Train.h"

class Customer {
    String firstname;
    String lastname;
    size_t siz;
    Date* dates;
    double* rounds;
    Train** trains;
    int* place;
public:
    Customer(String first ="" ,String last ="",size_t s = 0,Date* date1 = nullptr,double* rnds=nullptr  , Train** tr=nullptr, int* pl= nullptr) :firstname(first), lastname(last),
             siz(s),dates(new Date[s]),rounds(new double[s]),trains(new Train*[s]) , place(new int[s]) {
                for (size_t i= 0; i < s ; i++){
                    dates[i] = date1[i];
                    rounds[i] = rnds[i];
                    trains[i] = tr[i];
                    place[i] = pl[i];
                }
             };
    Customer(const Customer&);
    void printexact(std::ostream& os , Date d , Time t);
    bool same_name(String fs , String ls);
    Customer& operator+=(const Customer& cst);
    Date getDate(size_t r = 0);
    size_t size();
    void print(std::ostream& os);
    void printpartial(std::ostream& os,Date d);
    Customer& operator=(const Customer& cst);
    Time getdprt_timecust(size_t idx);
    ~Customer();
};
#endif
