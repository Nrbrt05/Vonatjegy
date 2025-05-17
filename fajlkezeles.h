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


std::string read_after_label(std::ifstream& is , std::string label);

Train* load_trains(size_t& siz);

Customer* load_custs(Train* trainz , size_t& custs_size);

void store_custs(Customer* custs , size_t custs_size);

void store_trains(Train* trs , size_t trains_size);
