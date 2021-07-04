// Copyright 2021 David Corbo

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <streambuf>

#include "./Parsetab.h"
#include "./Jobs.h"
#include "./Utils.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost::uuids;
using namespace boost::algorithm;
using boost::lexical_cast;

void illFormed(const char* place) {
    cerr << "The table file is ill formed. Please read the documentation";
    cerr << " to fix the table file or reset it from the remotely";
    cerr << " saved properly formed table file." << endl;
    cerr << endl;
    cerr << "The error occured around " << place << "." << endl;
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
    
    // split into sections
    vector<string> sections = split(full_file, "&&&");
    if (sections.size() != 3) {
        illFormed("bad section splitting");
    }
    Jobs jobs;
    string end_symbol(";&;");

    // parse job definition section
    string job_defs = sections[0];
    string start_symbol("$");
    size_t j_pos = 0;
    while ((j_pos = job_defs.find(start_symbol)) != string::npos) {
        size_t end_pos = job_defs.find(end_symbol, j_pos);
        string job_s = job_defs.substr(j_pos + 1, end_pos - j_pos - 1);

        // parse job
        Job job;
        vector<string> parts = split(job_s, ":&:");
        // parse id
        uuid id;
        try {
            id = lexical_cast<uuid>(parts[0]);
        } catch (...) {
            illFormed("uuid parsing");
        }
        job.set_id(id);

        // parse commands
        string open_symbol("{");
        string close_symbol("}");
        size_t open_pos = parts[1].find(open_symbol);
        size_t close_pos = parts[1].find(close_symbol);
        if (open_pos == string::npos || close_pos == string::npos) {
            illFormed("command list");
        }
        string commands = parts[1].substr(open_pos + 1,
            close_pos - open_pos - 1);
        trim(commands);
        if (commands.length() == 0) {
            illFormed("command list");
        }
        size_t nl_pos = 0;
        while ((nl_pos = commands.find('\n')) != string::npos) {
            string cmd_line = commands.substr(0, nl_pos);
            trim(cmd_line);
            if (cmd_line.length() != 0) {
                job.add_command(cmd_line);
            }
            commands.erase(0, nl_pos + 1);
        }
        trim(commands);
        if (commands.length() != 0) {
            job.add_command(commands);
        }

        // parse trees
        FormatTree input;
        
        if (!input.parse_tree(parts[2])) {
            illFormed("input format json parsing");
        }

        job.set_input(input);
        
        FormatTree output;

        if (!output.parse_tree(parts[3])) {
            illFormed("output format json parsing");
        }
        
        job.set_output(output);

        FormatTree sub_trigs;

        if (!sub_trigs.parse_tree(parts[4])) {
            illFormed("subsequent triggers format json parsing");
        }
        
        job.set_sub_trigs(sub_trigs);

        // checking job
        // cout << "uuid: " << job.get_id() << endl;
        // cout << "commands: " << endl;
        // for (auto it : job.get_commands()) {
        //     cout << it << endl;
        // }
        // cout << "input: " << endl;
        // job.get_input().print_tree();
        // cout << "output: " << endl;
        // job.get_output().print_tree();
        // cout << "subs: " << endl;
        // job.get_sub_trigs().print_tree();

        // stage 1 verification
        bool ver1 = job.verify_job_phase_1();
        if (!ver1) {
            illFormed("command and input parameter matching");
        }


        job_defs.erase(0, end_pos + end_symbol.length());
    }

    // parse alias section

    // parse instance section

    return true;
}
