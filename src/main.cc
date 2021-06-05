// Hopefully the beginning of something great

#include <iostream>
#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "./Parsetab.h"
#include "./Jobs.h"

using namespace std;
using namespace boost::uuids;

int main(int argc, char** argv) {
    string str;
    if (argc == 2) {
        str = string(argv[1]);
    }
    Jobs js;
    bool b = parseTab(str, &js);
    return 0;
}