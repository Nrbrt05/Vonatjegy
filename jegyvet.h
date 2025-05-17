#ifndef JEGYVET_H
#define JEGYVET_H

#include <iostream>
#include <iomanip>

#include "memtrace.h"

#include "Customer.h"
#include "string5.h"
#include "Time.h"
#include "Date.h"
#include "Train.h"
#include "jegyvet.h"

void jegyvetel(Customer*& custs , Train* trs,  size_t& custs_size , size_t trs_size);

#endif // JEGYVET_H
