#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <string>
#include <iomanip>

#include "memtrace.h"

#include "Customer.h"
#include "string5.h"
#include "Time.h"
#include "Date.h"
#include "Train.h"
#include "jegyvet.h"

void jegyvetel(Customer*& custs , Train* trs,  size_t& custs_size , size_t trs_size){

    std::srand(std::time(0));

    String fs_curr;
    String ls_curr;
    String dprt;
    String arriv;
    std::string line;
    std::cin.ignore(); //throw \n from last input (from the choice selection)
    std::cout << "Keresztnev(csak az angol abc betuit hasznald, illetve lehet szokozt, a vegen ne hagyj szokozt): ";
    std::getline(std::cin , line);
    fs_curr = String(line.c_str());
    std::cout << "Vezeteknev(csak az angol abc betuit hasznald, illetve lehet szokozt): ";

    std::getline(std::cin , line);
    ls_curr = String(line.c_str());
    std::cout << "Honnan(ne legyen benne spec. karakter)? ";
    std::cin >> dprt;
    std::cout << "Hova(csak az angol abc betuit hasznald, illetve lehet szokozt is)? ";
    std::cin >> arriv;
    std::cout << "Ev(csak egesz szamot irj): ";
    int yr_curr;
    std::cin >> yr_curr;
    std::cout << "Honap(csak egesz szamot irj): ";
    int month_curr;
    std::cin >> month_curr;
    std::cout << "Nap(csak egesz szamot irj): ";
    int day_curr;
    std::cin >> day_curr;
    Date dprt_date(yr_curr , month_curr , day_curr);
    Date dprt_date_ptr[1];
    dprt_date_ptr[0] = dprt_date;
    std::cout << "Mikor(formatum oraora:percperc)? ";
    int d_h;
    int d_m;
    char colon;
    std::cin >> std::setw(2) >> d_h >> colon >> std::setw(2) >> d_m;
    if(colon != ':'){
        std::cout << "Nem megfelelo formatum, vissza viszlek a fomenube";
        return;
    }
    Time dprt_t(d_h , d_m);
    std::cout << "Itt az osszes elerheto vonat a megadott idopont utan:\n";
    size_t which_train = 0;
    bool hadanytrain = false;
    for(size_t i = 0; i < trs_size ; i++){
        for(double rnd = 0 ; rnd <= trs[i].getround() ; rnd += 0.5){
            if(dprt == trs[i].getdprt(rnd) && arriv == trs[i].getarriv(rnd) && trs[i].getdprt_time(rnd) >= dprt_t){
                std::cout << which_train << ". " << std::endl;
                trs[i].printex(std::cout , rnd);
                hadanytrain = true;
                which_train++;
            }
        }
    }
    if(!hadanytrain){
        std::cout << "Sajnaljuk, nem volt a megadott idoponton vonat, probalja meg 00:00 idovel, es akkor az egesz napra latja a jaratokat, ha van egyaltalan" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }
    std::cout << "Kerem valasszon egyet(Csak egesz szamot irjon, pont nelkul, majd enter): ";
    size_t customers_choice;
    std::cin >> customers_choice;

    which_train = 0;
    bool done = false;
    bool hadcustomer = false;
    for(size_t i = 0; i < trs_size && !done ; i++){
        for(double rnd = 0 ; rnd < trs[i].getround() && !done ; rnd += 0.5){
            if(dprt == trs[i].getdprt(rnd) && arriv == trs[i].getarriv(rnd) && trs[i].getdprt_time(rnd) >= dprt_t){
                if(which_train == customers_choice){
                    for(size_t g = 0; g < custs_size ; g++){
                        if(custs[g].same_name(fs_curr , ls_curr)){
                            double rnd_ptr[1];
                            rnd_ptr[0] = rnd;
                            Train* tr_ptr[1];
                            tr_ptr[0] = &trs[i];
                            int plptr[1];
                            plptr[0] = (std::rand() % (trs[i].getcarts() + 1) );
                            custs[g]+= Customer("" , "" , 1 , dprt_date_ptr , rnd_ptr , tr_ptr , plptr);
                            std::cout << "Koszonjuk szepen, jegy felveve, ime:" << std::endl;
                            custs[g].printexact(std::cout , dprt_date , trs[i].getdprt_time(rnd));
                            hadcustomer = true;
                        }
                    }
                    if(!hadcustomer){
                        Customer* tmp = custs;
                        custs_size++;
                        Customer* ncusts = new Customer[custs_size];
                        for(size_t f = 0; f < custs_size - 1 ; f++){
                            ncusts[f] = tmp[f];
                        }
                        delete[] custs;
                        double rnd_ptr_nomatch[1];
                        rnd_ptr_nomatch[0] = rnd;
                        Train* tr_ptr_nomatch[1];
                        tr_ptr_nomatch[0] = &trs[i];
                        int plptr_nomatch[1];
                        plptr_nomatch[0] = (std::rand() % (trs[i].getcarts() + 1) );
                        ncusts[custs_size-1] = Customer(fs_curr , ls_curr , 1 , dprt_date_ptr , rnd_ptr_nomatch , tr_ptr_nomatch , plptr_nomatch);
                        custs = ncusts;
                        std::cout << "Koszonjuk szepen, jegy felveve, ime:" << std::endl;
                        custs[custs_size - 1].printexact(std::cout , dprt_date , trs[i].getdprt_time(rnd));
                    }
                    done = true;
                    break;
                }
                which_train++;
            }
        }
    }
    std::cout << "Amint keszen van a jegy informacionak ellenorzesevel nyomjon egyest, majd enter es vissza viszem a fomenube" << std::endl;
    int customers_choice_end;
    std::cin >> customers_choice_end;
    if (customers_choice_end != 1)
        std::cout << "Hibas bemenet, de vissza viszem a fomenube (adatok elmentve)" << std::endl;
    else std::cout << "Rendben, vissza viszem a fomenube"<<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return;
}
