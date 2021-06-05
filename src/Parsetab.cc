// Copyright 2021 David Corbo

#include <iostream>
#include <fstream>
#include <streambuf>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>

#include "./Parsetab.h"
#include "./Jobs.h"

using namespace std;
using namespace boost::uuids;
using namespace boost::algorithm;

bool parseTab(string& path, Jobs* j) {

    string file_ext(".ubicrontab");
    // string file_ext(".json");
    if (!ends_with(path, file_ext)) {
        cerr << "File could not be parsed, not an ubicron table file." << endl;
        return false;
    }
    ifstream f(&path[0]);
    if (!f.good()) {
        cerr << "The table file couldn't be opened" << endl;
        return false;
    }
    string full_file((istreambuf_iterator<char>(f)),
                    istreambuf_iterator<char>());
    
    vector<string> pieces;
    // write own splitting algorithm

    // boost::split(pieces, full_file, boost::is_any_of(";&;"));
    // cerr << pieces.size() << endl;
    // for (int i = 0; i < pieces.size(); i++) {
    //     cerr << i << ": " << pieces[i] << endl;
    // }

    // FormatTree ft(full_file);
    // cout << full_file << endl;
    return true;
}
