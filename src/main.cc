// Copyright 2021 David Corbo

// Currently just tests table parsing

#include <iostream>
#include <string>

#include "./Parsetab.h"
#include "./Jobs.h"
#include "./Remote.h"
#include "./Local.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

using namespace std;
using namespace boost::uuids;

bool startup(void);

bool new_dialogue(void);

bool connect_dialogue(void);

bool listen_locally(void);

//  Options: 
//  None: 
//      Performs regular startup. Reads table file, establishes connection with
//      ubicron.com, verifies that local jobs are valid, 
//      and listens for remote and local triggers
//  new:
//      starts the user interaction dialogue for creating a new local job
//  connect:
//      starts the user interaction dialogue for connecting to the
//      ubicron.com remote server

int main(int argc, char** argv) {
    string new_option("new");
    string connect_option("connect");
    if (argc == 1) {
        cout << "Beginnning general UbiCron startup" << endl;
        // general startup
        bool start = startup();
        if (!start) {
            cerr << "There was some error with startup" << endl;
            return 1;
        }
    } else if (argc == 2) {
        if (new_option.compare(argv[1])) {
            cout << "Creating new job" << endl;
        } else if (connect_option.compare(argv[1])) {
            cout << "Connecting to server" << endl;
        } else {
            cerr << argv[1] << " is not a known option." << endl;
        }

    }

    return 0;
}

// General startup:

// 1. Read and parse table file
// 2. Perform job verification stage 1
// 3. Establish remote connection
// 4. Perform job verification stage 2
// 5. Listen locally
// 6. Listen remotely
// 7. Begin job daemon

bool startup(void) {
    // read and parse table file
    string path("../testfiles/.ubicrontab");
    Jobs js;

    // perform job verification stage 1
    bool b = parseTab(path, &js);

    // establish remote connection
    Remote remote;
    if (!remote.full_connection()) {
        cerr << "idk" << endl;
    }
    cout << "Connection Established" << endl;

    // perform job verification stage 2
    map<string, FormatTree> remote_list;
    if (!remote.load_remote_jobs(remote_list&)) {
        cerr << "idk" << endl;
    }
    if (!jo)

    // listen locally

    // listen remotely

    // begin job daemon

    
    return b;
}

bool establish_connection(Remote remote) {
    return true;
}