#include <iostream>
#include <iomanip>
#include <string>
#include <thread>
#include <chrono>
#include "Train.h"
#include "Customer.h"

void jegymutatas(Customer* custs , Train* trs , size_t custs_size , size_t trs_size){
    std::string line;
    std::cin.ignore(); //throw \n from last input (from the choice selection)
    std::cout << "Keresztnev(csak az angol abc betuit hasznald, illetve lehet szokozt): ";
    std::getline(std::cin , line);
    String fs_curr = String(line.c_str());
    std::cout << "Vezeteknev(csak az angol abc betuit hasznald, illetve lehet szokozt): ";
    std::getline(std::cin , line);
    String ls_curr = String(line.c_str());
    std::cout << "Ev(csak egesz szamot irj): ";
    int yr_curr;
    std::cin >> yr_curr;
    std::cout << "Honap(csak egesz szamot irj): ";
    int month_curr;
    std::cin >> month_curr;
    std::cout << "Nap(csak egesz szamot irj): ";
    int day_curr;
    std::cin >> day_curr;
    Date date_curr(yr_curr , month_curr , day_curr);

    bool hadanytarget = false;
    for(size_t i = 0; i < custs_size ; i++){
        if(custs[i].same_name(fs_curr , ls_curr)){
            custs[i].printpartial(std::cout , date_curr);
            hadanytarget = true;
        }
    }

    if(!hadanytarget){
        std::cout << "Nem volt ilyen nev sajnos az adatbazisunkban, vissza viszem a fomenube" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    std::cout << "Kerem valasszon egy jegyet melyet meg akar nezni, az elotte allo szamot irja be legyen kedves." << std::endl;
    size_t customer_choice;
    std::cin >> customer_choice;
    std::cout << "-----------------------------------------" << std::endl;
    for(size_t i = 0; i < custs_size ; i++){
        if(custs[i].same_name(fs_curr , ls_curr)){
            custs[i].printexact(std::cout , date_curr , custs[i].getdprt_timecust(customer_choice));
        }
    }
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "Kerem ha vegzett a jegy informaciok ellenorzesevel akkor nyomjon egyest, es vissza viszem a fomenube." << std::endl;
    int customer_ch_end;
    std::cin >> customer_ch_end;
    if(customer_ch_end != 1)
        std::cout << "Hibas formatum, de vissza viszem a fomenube (nincs szukseg adatmentesre)"<<std::endl;
    std::cout << "Rendben, vissza viszem a fomenube (nincs szukseg adatmentesre)" << std::endl;

    return;

}
