// Copyright 2021 David Corbo

#include <iostream>
#include <fstream>
#include <streambuf>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/algorithm/string/predicate.hpp>


#include "./Parsetab.h"

using namespace std;
using namespace boost::uuids;
using namespace boost::algorithm;

Jobs parseTab(string& path) {
    string file_ext(".ubicrontab");
    if (!ends_with(path, file_ext)) {
        cerr << "File could not be parsed, not an ubicron table file." << endl;
        return Jobs();
    }
    ifstream f(&path[0]);
    if (!f.good()) {
        cerr << "The table file couldn't be opened" << endl;
        return Jobs();
    }
    string full_file((istreambuf_iterator<char>(f)),
                    istreambuf_iterator<char>());
    cout << full_file << endl;
    return Jobs();
}
