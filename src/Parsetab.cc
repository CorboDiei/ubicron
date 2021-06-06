// Copyright 2021 David Corbo

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <streambuf>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>

#include "./Parsetab.h"
#include "./Jobs.h"
#include "./Utils.h"

using namespace std;
using namespace boost::uuids;
using namespace boost::algorithm;

void illFormed(void) {
    cerr << "The table file is ill formed. Please read the documentation";
    cerr << " to fix the table file or reset it from the remotely";
    cerr << " saved properly formed table file." << endl;
    exit(EXIT_FAILURE);
}

bool parseTab(string& path, Jobs* j) {
    // extract table file intro string
    string file_ext(".ubicrontab");
    if (!ends_with(path, file_ext)) {
        cerr << "File could not be parsed, not an ubicron table file." << endl;
        exit(EXIT_FAILURE);
    }
    ifstream f(&path[0]);
    if (!f.good()) {
        cerr << "The table file couldn't be opened" << endl;
        exit(EXIT_FAILURE);
    }
    string full_file((istreambuf_iterator<char>(f)),
                    istreambuf_iterator<char>());

    // remove comments from table file
    string delim("%%");
    size_t c_pos = 0;
    while ((c_pos = full_file.find(delim)) != string::npos) {
        size_t nl = full_file.find('\n', c_pos);
        full_file.erase(c_pos, nl - c_pos + 1);
    }
    cerr << full_file << endl;

    
    
    // vector<string> pieces = split(full_file, ";&;");

    // cerr << pieces.size() << endl;
    // for (unsigned int i = 0; i < pieces.size(); i++) {
    //     cerr << i << ": " << pieces[i] << endl;
    // }

    // FormatTree ft(full_file);
    // cout << full_file << endl;
    return true;
}
