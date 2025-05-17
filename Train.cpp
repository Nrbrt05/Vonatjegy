#include <iostream>
#include <cmath>
#include <iomanip>
#include "memtrace.h"
#include "Train.h"
#include "string5.h"
#include "Time.h"

void Train::printex(std::ostream& os,double r){ //int: which departure,first is r = 0, 0.5 is the first way back, 1.5 and so on are the ways back
    if (r >= round)
        return;
    os << "Azonosito: " << Id;
    os << std::endl << "Indulasi ido: ";
    getdprt_time(r).print(os);
    os<<std::endl;
    os << "Kocsik szama: " <<
    carts << std::endl << "Indulasi hely: " << getdprt(r) << std::endl <<
    "Erkezesi hely: ";
    if(fmod(r / 0.5 , 2.0) != 0.0)
        os << dprt;
    else os << arriv;
    os << std::endl << "Erkezesi ido: ";
    Time arrival(getdprt_time(r)+trip);
    arrival.print(os);
    os<<std::endl;
}

void Train::print(std::ostream& os) {
    os << "Azonosito: " << Id;
    os << std::endl << "Indulasi ido: ";
    dprt_time.print(os);
    os<<std::endl;
    os << "Kocsik szama: " <<
    carts << std::endl << "Indulasi hely: " << dprt << std::endl <<
    "Erkezesi hely: " << arriv << std::endl;
    os << "Oda ut: ";
    trip.print(os);
    os << std::endl;
    os << "Korok: " << round;
    os<<std::endl;
}

Time Train::getdprt_time(double r){ //int: which departure,first is r = 0, 0.5 is the first way back, 1.5 and so on are the ways back
    Time res(dprt_time);
    for (double i = 0.0 ; i < r ; i++) {
        if (r-i == 0.5)
            res = res + trip;
        else res = res + trip + trip;
    }
    return res;
}

String Train::getdprt(double r){
    if (fmod(r / 0.5 , 2.0) != 0.0)
        return arriv;
    else return dprt;
}
String Train::getarriv(double r) {
    if (fmod(r / 0.5 , 2.0) != 0.0)
        return dprt;
    else return arriv;
}

Train& Train::operator=(const Train& t){
    Id = t.Id;
    carts = t.carts;
    dprt = t.dprt;
    arriv=t.arriv;
    dprt_time = t.dprt_time;
    trip = t.trip;
    round = t.round;
    return *this;
}
int Train::getcarts(){
    return carts;
}
int Train::getId(){
    return Id;
}
int Train::getround(){
    return round;
}
Time Train::gettrip(){
    return trip;
}

Train::~Train(){
    Id = 0;
    carts = 0;
    dprt = "";
    arriv="";
    dprt_time = Time(0 , 0);
    trip = Time(0,0);
    round = 0;
}
