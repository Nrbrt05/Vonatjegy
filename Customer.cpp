#include <iostream>
#include <iomanip>
#include "memtrace.h"
#include "Customer.h"
#include "Date.h"
#include "Train.h"
#include "string5.h"
#include "Time.h"


Customer::Customer(const Customer& cust) {
    firstname = cust.firstname;
    lastname = cust.lastname;
    siz = cust.siz;

    dates = new Date[siz];
    rounds = new double[siz];
    trains = new Train*[siz];
    place = new int[siz];

    for(size_t i = 0; i < siz ; i++){
        dates[i] = cust.dates[i];
        rounds[i] = cust.rounds[i];
        trains[i] = cust.trains[i];
        place[i] = cust.place[i];
    }
}


bool Customer::same_name(String fs , String ls){
    if((firstname == fs && lastname ==ls))
        return true;
    return false;
}

Customer& Customer::operator+=(const Customer& cst){
    Customer tmp = *this;
    delete[] dates;
    delete[] rounds;
    delete[] trains;
    delete[] place;
    siz++;
    dates = new Date[siz];
    rounds = new double[siz];
    trains = new Train*[siz];
    place = new int[siz];

    for (size_t i = 0; i < siz-1 ; i++){
        dates[i] = tmp.dates[i];
        rounds[i] = tmp.rounds[i];
        trains[i] = tmp.trains[i];
        place[i] = tmp.place[i];
    }
    dates[siz-1] = cst.dates[0];
    rounds[siz-1] = cst.rounds[0];
    trains[siz-1] = cst.trains[0];
    place[siz-1] = cst.place[0];

    return *this;
}

size_t Customer::size(){
    return siz;
}

Date Customer::getDate(size_t r) {
    return dates[r];
}

void Customer::print(std::ostream& os){
    for (size_t i = 0; i < siz ; i++){
            os<<"Keresztnev: " << firstname <<std::endl << "Vezeteknev: " << lastname << std::endl;
            os<< "Hely: " << place[i]<<std::endl;
            os << "Ervenyes(indulasi datum, azonosito, ido):"<<std::endl;
            dates[i].print(os);
            os<<std::endl;
            trains[i]->printex(os,rounds[i]);
            os << "&" << std::endl;
    }
}

void Customer::printexact(std::ostream& os , Date d , Time t){
    for (size_t i = 0; i < siz ; i++){
            if(d == dates[i] && trains[i]->getdprt_time(rounds[i]) == t) {
            os<<"Keresztnev: " << firstname <<std::endl << "Vezeteknev: " << lastname << std::endl;
            os<< "Hely: " << place[i]<<std::endl;
            os << "Ervenyes(indulasi datum, azonosito, ido):"<<std::endl;
            dates[i].print(os);
            os<<std::endl;
            trains[i]->printex(os,rounds[i]);
            }
    }
}

void Customer::printpartial(std::ostream& os,Date d){
    for (size_t i = 0; i < siz; i++){
        if(d == this->dates[i]){
            os << i << "." << std::endl;
            os << "Indulasi hely: " <<
            trains[i]->getdprt(rounds[i])<< " " << "Indulasi ido: ";
            trains[i]->getdprt_time(rounds[i]).print(os);
            os<<std::endl;
        }
    }
}

Customer& Customer::operator=(const Customer& cst){

    if (this == &cst) return *this;

    firstname = cst.firstname;
    lastname = cst.lastname;

    siz = cst.siz;

    delete[] dates;
    delete[] rounds;
    delete[] trains;
    delete[] place;

    dates = new Date[siz];
    rounds = new double[siz];
    trains = new Train*[siz];
    place = new int[siz];

    for (size_t i = 0; i < siz ; i++){
        dates[i] = cst.dates[i];
        rounds[i] = cst.rounds[i];
        trains[i] = cst.trains[i];
        place[i] = cst.place[i];
    }
    return *this;
}

Time Customer::getdprt_timecust(size_t idx){
    return trains[idx]->getdprt_time(rounds[idx]);
}

Customer::~Customer(){
    firstname="";
    lastname="";
    siz = 0;
    delete[] dates;
    delete[] trains;
    delete[] rounds;
    delete[] place;
}
