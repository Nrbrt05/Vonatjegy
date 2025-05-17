#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>

#include "Date.h"
#include "Time.h"
#include "string5.h"
#include "Train.h"
#include "Customer.h"
#include "fajlkezeles.h"
#include "vonatfelv.h"
#include "jegyvet.h"
#include "jegymut.h"
#include "memtrace.h"

int main(void) {

int state = 0; //state variable, closes the console when -1
//creating two arrays, one for the customers, and one for the trains
//we first initialize the trains, because that will be our parameter for loading the customers
size_t custs_size = 0;
size_t trs_size = 0;
Train* trs = load_trains(trs_size);
Customer* custs = load_custs(trs , custs_size);

size_t tmptrssiz;
//Starting the FSM
while (state != -1) {
//States
    switch(state){
        case 0:
            std::cout << R"(

   ___      ___ ________  ________   ________  _________           ___  _______   ________      ___    ___
  |\  \    /  /|\   __  \|\   ___  \|\   __  \|\___   ___\        |\  \|\  ___ \ |\   ____\    |\  \  /  /|
  \ \  \  /  / | \  \|\  \ \  \\ \  \ \  \|\  \|___ \  \_|        \ \  \ \   __/|\ \  \___|    \ \  \/  / /
   \ \  \/  / / \ \  \\\  \ \  \\ \  \ \   __  \   \ \  \       __ \ \  \ \  \_|/_\ \  \  ___   \ \    / /
    \ \    / /   \ \  \\\  \ \  \\ \  \ \  \ \  \   \ \  \     |\  \\_\  \ \  \_|\ \ \  \|\  \   \/  /  /
     \ \__/ /     \ \_______\ \__\\ \__\ \__\ \__\   \ \__\    \ \________\ \_______\ \_______\__/  / /
      \|__|/       \|_______|\|__| \|__|\|__|\|__|    \|__|     \|________|\|_______|\|_______|\___/ /
                                                                                              \|___|/


    )";
            int firstchoice;
            std::cout << std::endl << "Milyen muveletet szeretnel elvegezni?(Csak egesz szamot, pont nelkul irj, majd enter)\n1. Vonat felvetele\n2. Jegy vetele\n3. Jegy megmutatasa\n-1. Kilepes\n";
            std::cin >>firstchoice;
            state = firstchoice;
            break;
        case 1:
            tmptrssiz = trs_size;
            vonatfelvetel(trs , trs_size);
            if(tmptrssiz != trs_size)
                store_trains(trs , trs_size);
            state = 0;
            break;
        case 2:
            delete[] trs;
            trs_size = 0;
            trs = load_trains(trs_size);
            delete[] custs;
            custs = load_custs(trs , custs_size);
            jegyvetel(custs , trs , custs_size , trs_size);
            store_custs(custs , custs_size);
            state = 0;
            break;
        case 3:
            jegymutatas(custs , trs , custs_size , trs_size);
            state = 0;
            break;
        case -1:
            break;
    }
}
//felszabaditas
delete[] trs;
delete[] custs;
return 0;
}

