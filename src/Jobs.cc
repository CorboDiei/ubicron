// Copyright 2021 David Corbo

#include <cstdint>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "./Jobs.h"

#include "./thirdparty/json.hpp"

using namespace std;
using namespace boost::uuids;
using json = nlohmann::json;

FormatTree::FormatTree(string json_text) {
    tree = json::parse(&json_text[0]);
    cout << tree.dump(4) << endl;

}

bool FormatTree::verify_tree(FormatType type) {

}

string FormatTree::get_value(string query) {
    
}

Job::Job(uuid id, vector<string> commands, FormatTree input,
    FormatTree output, FormatTree sub_trigs) {
        job_id_ = id;
        commands_ = commands;
        verified_ = true;
        if (!input.verify_tree(FormatType::input)) {
            cerr << "The input tree is not valid" << endl;
            verified_ = false;
        }
        if (!output.verify_tree(FormatType::output)) {
            cerr << "The output tree is not valid" << endl;
            verified_ = false;
        }
        if (!sub_trigs.verify_tree(FormatType::sub_triggers)) {
            cerr << "The subsequent triggers tree is not valid" << endl;
            verified_ = false;
        }
    }