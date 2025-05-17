#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include "memtrace.h"

#include "Date.h"
#include "Time.h"
#include "string5.h"
#include "Train.h"
#include "Customer.h"
#include "fajlkezeles.h"


std::string read_after_label(std::ifstream& is , std::string label) {
    std::string line;
    std::getline(is , line);
    size_t colon_pos = line.find(':');
    if(colon_pos == std::string::npos || line.substr(0,colon_pos+1) != label)
        return std::string("no label");
    std::string value = line.substr(colon_pos + 1);
    value.erase(0 , value.find_first_not_of(" \t"));
    return value;
}


Train* load_trains(size_t& siz) {
    Train* trs=nullptr;
    std::ifstream file("database_trains.txt");
    char c;
    while (file >> c) {
            if (c == '&')
                siz++;
        }
    file.clear(); //clear flags like eof
    file.seekg(0); //read pointer to the beginning
    if (siz == 0) return nullptr;
    trs = new Train[siz];
    for (size_t i = 0 ; i < siz ; i++) {
    String dummy;
    int Id_curr;
    file >> dummy >> Id_curr; //Azonosito
    file >> dummy >> dummy; //1.Indulas 2.ido:
    //dprt_time.print(os);
    int dhour_curr;
    int dmin_curr;
    char colon;
    file >> std::setw(2) >> dhour_curr >> colon >> colon >> std::setw(2) >> dmin_curr;
    Time dprt_t_curr = Time(dhour_curr , dmin_curr);
    int carts_curr;
    String dprt_curr;
    String arriv_curr;
    file >> dummy >> dummy >> //1. "Kocsik" , 2. "szama:"
    carts_curr >> dummy >> dummy >> dprt_curr >> //1.Indulasi 2.hely:
    dummy >> dummy >> arriv_curr; //"1.Erkezesi 2.hely: "
    //1.Oda 2.ut:
    file >> dummy >> dummy;
    int thour_curr;
    int tmin_curr;
    file >> std::setw(2) >> thour_curr >> colon >> colon >> std::setw(2) >> tmin_curr;
    Time trip_curr = Time(thour_curr , tmin_curr);
    //"Korok: "
    int r_curr;
    file >> dummy >> r_curr;
    char ampersand;
    file >> ampersand;
    trs[i] = Train(Id_curr , carts_curr , dprt_curr , arriv_curr , dprt_t_curr , trip_curr, r_curr);
    }
    file.close();
    return trs;
}

Customer* load_custs(Train* trainz , size_t& custs_size) {
    char c;
    size_t size_tickets = 0;
    size_t start = 0;


    std::ifstream file("database_custs.txt");
        while (file >> c) {
            if (c == '&')
                size_tickets++;
        }
        c = 'a';
        if (size_tickets == 0)
            return nullptr;
        file.clear(); //clear flags like eof
        file.seekg(0); //read pointer to the beginning
        size_t size_custs = 1;


        //watch how many customers are in the file
        String first_firstname1 = String(read_after_label(file , "Keresztnev:").c_str());
        String first_lastname1 = String(read_after_label(file , "Vezeteknev:").c_str());
        if (first_firstname1 == "no label" || first_lastname1 == "no label")
            return nullptr;
        for (size_t i = 0; i < size_tickets-1 ; i++) {
            while(file >> c && c!= '&');
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            String second_firstname1 = String(read_after_label(file , "Keresztnev:").c_str());
            String second_lastname1 = String(read_after_label(file , "Vezeteknev:").c_str());
            if (second_firstname1 != first_firstname1 && second_lastname1 != first_lastname1){
                size_custs++;
                first_firstname1 = second_firstname1;
                first_lastname1 = second_lastname1;
            }
        }
        file.clear(); //clear flags like eof
        file.seekg(0); //read pointer to the beginning
        //Watch what the size of each customer is
        size_t* custs_sizes = new size_t[size_custs]();

        String first_firstname2 = String(read_after_label(file , "Keresztnev:").c_str());
        String first_lastname2 = String(read_after_label(file , "Vezeteknev:").c_str());
        if (first_firstname2 == "no label" || first_lastname2 == "no label"){
            delete[] custs_sizes;
            return nullptr;
        }
        size_t g = 0; //which customer
        custs_sizes[0] = 1;
        for (size_t i = 0; i < size_tickets-1 ; i++) {
            while(file >> c && c!= '&');
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            String second_firstname2 = String(read_after_label(file , "Keresztnev:").c_str());
            String second_lastname2 = String(read_after_label(file , "Vezeteknev:").c_str());
            if (second_firstname2 == "no label" || second_lastname2 == "no label")
                break;
            if (second_firstname2 != first_firstname2 && second_lastname2 != first_lastname2){
                custs_sizes[++g]++;
                first_firstname2 = second_firstname2;
                first_lastname2 = second_lastname2;
            } else{
                custs_sizes[g]++;
            }
        }
        file.clear(); //clear flags like eof
        file.seekg(0); //read pointer to the beginning

        Customer* custs = new Customer[size_custs];
        //customer data:
        String* lss = new String[size_custs];
        String* fss = new String[size_custs];
        Date** dts = new Date*[size_custs];

        Train*** trs = new Train**[size_custs];
        //data for the customer, and connected to the train
        double** rnds = new double*[size_custs];
        int** places = new int*[size_custs];

        for(size_t i = 0; i < size_custs ; i++){
            places[i] = new int[custs_sizes[i]];
            rnds[i] = new double[custs_sizes[i]];
            dts[i] = new Date[custs_sizes[i]];
            trs[i] = new Train*[custs_sizes[i]]();
        }

            while (start != size_tickets) {
            String dummy;
            //namecurr
            String fs_curr;
            String ls_curr;
            //place
            int place_curr;
            //datecurr
            int yr_curr;
            int m_curr;
            int d_curr;
            //Idcurr
            int Id_curr;
            //round_curr
            double round_current = 0.0;
            //dprt_timecurr
            int dprt_time_hour_current;
            int dprt_time_min_current;
            //carts_curr
            int carts_curr;
            //dprt
            String dprt_curr;
            //arriv
            String arriv_curr;
            //arrival time
            int arriv_h_curr;
            int arriv_min_curr;

            fs_curr = String(read_after_label(file , "Keresztnev:").c_str());//Keresztnev: , can read multi-word First names
            ls_curr = String(read_after_label(file , "Vezeteknev:").c_str());//Vezeteknev: , can read multi-word Last names
            file >> dummy >> place_curr; //Hely:
            file >> dummy >> dummy >> dummy >> dummy; //1."Ervenyes(indulasi" 2."datum," 3."azonosito," 4."ido):"
            //d.print
            char dot;
            file >> std::setw(4) >> yr_curr >> dot >> std::setw(2) >> m_curr >> dot >> std::setw(2)>> d_curr;

            Date date_curr(yr_curr , m_curr , d_curr); //date_curr

            //train.print()
            file >> dummy >> Id_curr; //Azonosito:
            file >> dummy >> dummy; //1."Indulasi" "ido:"
            //getdprt_time(r).print()
            char colon;

            file >> std::setw(2) >> dprt_time_hour_current >> colon >> colon >>std::setw(2) >> dprt_time_min_current;
            Time dprt_time_curr(dprt_time_hour_current, dprt_time_min_current);

            file >> dummy >> dummy >> //Kocsik 1. str szama: 2.str
            carts_curr >> dummy >> dummy >> dprt_curr >> //1."Indulasi" 2."hely"
            dummy >> dummy; //1."Erkezesi" 2."hely"
            file >> arriv_curr;
            file >> dummy >> dummy; //1."Erkezesi" 2."ido"
            file >> arriv_h_curr >> colon >> colon >> arriv_min_curr;
            char ampersand;
            file >> ampersand;
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //which train:
            std::ifstream filetrs("database_trains.txt");
            size_t size_trs = 0;
                while (filetrs >> c) {
                    if (c == '&')
                    size_trs++;
                }
            filetrs.close();

            Train* tr_currptr;
            for (size_t i = 0; i < size_trs ; i++){
                if(Id_curr == trainz[i].getId())
                    tr_currptr = &trainz[i];
            }
            //which round:
            while(!(dprt_time_curr == tr_currptr->getdprt_time(round_current))){
                round_current = round_current + 0.5;
            }
            //Which customer we're at:
            //size_t cust_which = 0;
            //size_t for what index we are within a customer:
            //size_t cust_idx = 0;
            //whether we find a match for a customer
            bool hadtarget = false;
            for(size_t i = 0; i < size_custs && !hadtarget ; i++){
                for(size_t g = 0 ; g < custs_sizes[i] && !hadtarget ; g++){
                    if (trs[i][g] == nullptr){
                        lss[i] = ls_curr;
                        fss[i] = fs_curr;
                        dts[i][g] = date_curr;
                        trs[i][g] = tr_currptr;
                        rnds[i][g] = round_current;
                        places[i][g] = place_curr;
                        hadtarget = true;
                    }
                }
            }

            start++;

        }
        for (size_t i = 0; i < size_custs ; i++){
            custs[i] = Customer(fss[i] , lss[i] , custs_sizes[i] , dts[i] , rnds[i] , trs[i] , places[i]);
        }
    file.close();
    custs_size = size_custs;
    for(size_t i = 0; i < size_custs ; i++){
            delete[] places[i];
            delete[] rnds[i];
            delete[] dts[i];
            delete[] trs[i];
    }
    delete[] custs_sizes;
    delete[] lss;
    delete[] fss;
    delete[] dts;
    delete[] trs;
    delete[] rnds;
    delete[] places;
    return custs;
}

void store_custs(Customer* custs , size_t custs_size) {
    std::ofstream file("database_custs.txt");
        for (size_t i = 0; i < custs_size ; i++){
            custs[i].print(file);
        }
    file.close();
}

void store_trains(Train* trs , size_t trains_size) {
    std::ofstream file("database_trains.txt");
        for (size_t i = 0; i < trains_size ; i++) {
            trs[i].print(file);
            file << "&" << std::endl;
        }
    file.close();
}
