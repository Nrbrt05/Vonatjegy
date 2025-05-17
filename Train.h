#ifndef TRAIN_H
#define TRAIN_H

#include <iostream>
#include <iomanip>
#include "memtrace.h"
#include "string5.h"
#include "Date.h"
#include "Time.h"

class Train {
    int Id;
    int carts;
    String dprt;
    String arriv;
    Time dprt_time;
    Time trip;
    int round;
public:
    Train(int id_nmbr = 0, int crts = 0, String dprt_p="",String arriv_p="", Time d_t = Time(0,0),
          Time trp = Time(0,0), int rnd= 0) :Id(id_nmbr) , carts(crts) , dprt(dprt_p) , arriv(arriv_p),
          dprt_time(d_t) , trip(trp) , round(rnd) {};
    void printex(std::ostream& , double r = 0); //int: which departure,first is r = 0, 0.5 is the first way back, 1.5 and so on are the ways back
    void print(std::ostream&);
    Time getdprt_time(double r = 0); //int: which departure,first is r = 0, 0.5 is the first way back, 1.5 and so on are the ways back
    String getdprt(double r = 0.0);
    Train& operator=(const Train&);
    int getcarts();
    int getId();
    int getround();
    String getarriv(double r = 0);
    Time gettrip();
    ~Train();
};

#endif
