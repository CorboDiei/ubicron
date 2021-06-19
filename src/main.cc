// Copyright 2021 David Corbo

// Currently just tests table parsing

#include <iostream>
#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "./Parsetab.h"
#include "./Jobs.h"
#include "./Remote.h"

using namespace std;
using namespace boost::uuids;

bool startup(void);

bool establish_connection(Remote remote);

int main(int argc, char** argv) {
    if (argc == 1) {
        // general startup
        bool start = startup();
        if (!start) {
            cerr << "There was some error with startup" << endl;
            return 1;
        }

    }

    return 0;
}

// General startup:

// 1. Read and parse table file
// 2. Perform job verification stage 1
// 3. Establish remote connection
// 4. Perform job verification stage 2
// 5. 

bool startup(void) {
    string path("../testfiles/.ubicrontab");
    Jobs js;
    bool b = parseTab(path, &js);
    return b;
}

bool establish_connection(Remote remote) {
    return true;
}