// Copyright 2021 David Corbo

#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "./Utils.h"

using namespace std;
using namespace boost::algorithm;

vector<string> split(string str, const char* del) {
    string delim(del);
    vector<string> vec;
    string token;
    size_t pos = 0;
    while ((pos = str.find(delim)) != string::npos) {
        token = str.substr(0, pos);
        trim(token);
        vec.push_back(token);
        str.erase(0, pos + delim.length());
    }
    trim(str);
    if (str.length() != 0) {
        vec.push_back(str);
    }
    return vec;
}