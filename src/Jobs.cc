// Copyright 2021 David Corbo

#include <cstdint>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <typeinfo>

#include "./Jobs.h"
#include "./Utils.h"

#include "./thirdparty/json.hpp"
#include <boost/uuid/uuid.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>


using namespace std;
using namespace boost::uuids;
using namespace boost::algorithm;
using boost::lexical_cast;
using json = nlohmann::json;

void recursive_iterate(const json& j, vector<string>& vec);

bool FormatTree::parse_tree(string& json_text) {
    try {
        tree_ = json::parse(&json_text[0]);
    } catch (...) {
        return false;
    }
    return true;
}

string FormatTree::get_value(string query) {
    string failure("&failure&");
    string res;
    vector<string> tokens = split(query, ".");
    auto cur = tree_;
    for (unsigned int i = 0; i < tokens.size(); i++) {
        try {
            cur = cur.at(tokens[i]);
        } catch (nlohmann::detail::type_error& e) {
            try {
                cur = cur[lexical_cast<int>(tokens[i])];
            } catch (...) {
                return failure;
            }
        } catch (nlohmann::detail::out_of_range& e) {
            return failure;
        }
    }
    res = lexical_cast<string>(cur);
    return res;
}

void recursive_iterate(const json& j, vector<string>& vec) {
    for (auto it = j.begin(); it != j.end(); it++) {
        if (it->is_structured()) {
            recursive_iterate(*it, vec);
        } else {
            try {
                vec.push_back(lexical_cast<string>(*it));
            } catch (...) {
                continue;
            }
        }
    }
}

vector<string> FormatTree::get_values() {
    vector<string> vec;
    recursive_iterate(tree_, vec);
    return vec;
}

void FormatTree::print_tree(void) {
    cout << tree_.dump(4) << endl;
}

Job::Job(uuid id, vector<string> commands, FormatTree input,
        FormatTree output, FormatTree sub_trigs) {
    job_id_ = id;
    commands_ = commands;
    on_command_ = 0;
    // verified_ = true;

    // changing verification method
    // if (!input.verify_tree(FormatType::input)) {
    //     cerr << "The input tree is not valid" << endl;
    //     verified_ = false;
    // }
    // if (!output.verify_tree(FormatType::output)) {
    //     cerr << "The output tree is not valid" << endl;
    //     verified_ = false;
    // }
    // if (!sub_trigs.verify_tree(FormatType::sub_triggers)) {
    //     cerr << "The subsequent triggers tree is not valid" << endl;
    //     verified_ = false;
    // }
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

void Job::set_input(FormatTree input) {
    input_ = input;
}

void Job::set_output(FormatTree output) {
    output_ = output;
}

void Job::set_sub_trigs(FormatTree sub_trigs) {
    sub_triggers_ = sub_trigs;
}

bool Job::verify_job_phase_1(void) {
    // check that variable params used in commands is subset of 
    // input params

    // get list of variable params
    vector<string> var_params;
    for (string command : commands_) {
        for (string token : split(command, " ")) {
            if (token[0] == '@') {
                token = token.erase(0, 1);
                var_params.push_back(token);
            }
        }
    }
    string failure("&failure&");
    for (auto it : var_params) {
        if ((failure.compare(input_.get_value(it))) == 0) {
            return false;
        }
    }

    // check that output value line values are less than or
    // equal to the number of commands

    for (auto it : output_.get_values()) {
        string str = split(it, ".")[0];
        str = str.erase(0, 1);
        unsigned int val = lexical_cast<unsigned int>(str);
        if (val > commands_.size()) {
            return false;
        }
    }
    
    return true;
}
