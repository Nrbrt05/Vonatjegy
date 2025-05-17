#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include "vonatfelv.h"

void vonatfelvetel(Train*& trs , size_t& trs_size){
    std::cout << "VONATFELVETELT VALASZTOTTA, KEREM ADJA MEG A KOVETKEZO ADATOKAT:\n";
    std::cout << "Vonat azonosito szama (csak egesz szamot irj!): ";
    int Id_curr; //ID
    std::cin >> Id_curr;
    for (size_t i  = 0 ; i < trs_size ; i++){
        if(trs[i].getId() == Id_curr){
            std::cout << "Mar volt ez a vonat, vissza viszlek a fomenube" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            return;
        }
    }
    std::cout << "Hany kocsija van (csak egesz szamot irj!)? ";
    int carts_curr;
    std::cin >> carts_curr;
    std::cout << "Indulasi allomas (csak az angol abc betuit hasznald, illetve lehet szokozt): ";
    String dprt;
    std::cin >> dprt;
    std::cout << "Erkezesi allomas (csak az angol abc betuit hasznald, illetve lehet szokozt): ";
    String arriv;
    std::cin >> arriv;
    std::cout << "Indulasi ido (formatum: oraora:percperc): ";
    int d_h;
    int d_m;
    char colon;
    std::cin >> std::setw(2) >> d_h >> colon >> std::setw(2) >> d_m;
    if (colon != ':'){
        std::cout << "Nem megfelelo formatum, vissza viszlek a fomenube" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }
    Time dprt_t(d_h , d_m);
    std::cout << "Mennyi ido az ut oda(formatum: oraora:percperc)? ";
    int t_h;
    int t_m;
    std::cin >> std::setw(2) >> t_h >> colon >> std::setw(2) >> t_m;
    if (colon != ':'){
        std::cout << "Nem megfelelo formatum, vissza viszlek a fomenube" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }
    Time trip_t(t_h , t_m);
    std::cout << "Hanyszor tesz meg oda-visszat egy nap alatt(csak egesz szamot irj!)? ";
    int round;
    std::cin >> round;
    Train* tmp = trs;
    Train* ntrs = new Train[trs_size + 1];
    trs_size++;
    for (size_t i = 0 ; i < trs_size-1 ; i++){
        ntrs[i] = tmp[i];
    }
    delete[] trs;
    ntrs[trs_size-1] = Train(Id_curr , carts_curr , dprt , arriv , dprt_t , trip_t , round);
    trs = ntrs;

    std::cout << "Koszonom szepen, vissza viszem a fomenube";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return;
}
