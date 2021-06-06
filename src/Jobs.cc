// Copyright 2021 David Corbo

#include <cstdint>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "./Jobs.h"

#include "./thirdparty/json.hpp"

using namespace std;
using namespace boost::uuids;
using namespace boost::algorithm;
using json = nlohmann::json;

FormatTree::FormatTree(string json_text) {
    tree_ = json::parse(&json_text[0]);
    type_ = FormatType::unset;
}

bool FormatTree::verify_tree(FormatType type) {
    // for now
    return true;

    if (type == type_) {
        return true;
    } else if (type == FormatType::input) {

    } else if (type == FormatType::output) {

    } else if (type == FormatType::sub_triggers) {

    }
    return false;
}

string FormatTree::get_value(string query) {
    
}

Job::Job(uuid id, vector<string> commands, FormatTree input,
    FormatTree output, FormatTree sub_trigs) {
    job_id_ = id;
    commands_ = commands;
    on_command_ = 0;
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

string Job::get_next_command(void) {
    if (on_command_ == commands_.size()) {
        return string("failure");
    }
    string cmd = commands_[on_command_];
    on_command_++;
    return cmd;
}

bool Job::add_command(string command) {
    trim(command);
    if (command.length() == 0) {
        return false;
    }
    commands_.push_back(command);
    return true;
}

bool Job::set_input(FormatTree input) {
    if (!input.verify_tree(FormatType::input)) {
        return false;
    }
    input_ = input;
    return true;
}

bool Job::set_output(FormatTree output) {
    if (!output.verify_tree(FormatType::output)) {
        return false;
    }
    output_ = output;
    return true;
}

bool Job::set_sub_trigs(FormatTree sub_trigs) {
    if (!sub_trigs.verify_tree(FormatType::sub_triggers)) {
        return false;
    }
    sub_triggers_ = sub_trigs;
    return true;
}