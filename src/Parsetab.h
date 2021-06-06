// Copyright 2021 David Corbo

#ifndef PARSETAB_H_
#define PARSETAB_H_

#include <iostream>
#include <cstdint>
#include <string>

#include "./Jobs.h"

using namespace std;

// Parses the table at the passed address, 
// returns a new jobs object that 

void illFormed(void);

bool parseTab(string& path, Jobs* j);


#endif  // PARSETAB_H_