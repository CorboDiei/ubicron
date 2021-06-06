// Copyright 2021 David Corbo

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <streambuf>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

#include "./Parsetab.h"
#include "./Jobs.h"
#include "./Utils.h"

using namespace std;
using namespace boost::uuids;
using namespace boost::algorithm;
using boost::lexical_cast;

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
    
    // split into sections
    vector<string> sections = split(full_file, "&&&");
    if (sections.size() != 3) {
        illFormed();
    }
    Jobs jobs;
    string end_symbol(";&;");

    // parse job definition section
    string job_defs = sections[0];
    string start_symbol("$");
    size_t j_pos = 0;
    while ((j_pos = job_defs.find(start_symbol)) != string::npos) {
        size_t end_pos = job_defs.find(end_symbol, j_pos);
        string job_s = job_defs.substr(j_pos + 1, end_pos - j_pos);

        // parse job
        Job job;
        vector<string> parts = split(job_s, ":&:");
        // parse id
        uuid id = lexical_cast<uuid>(parts[0]);
        job.set_id(id);
        cerr << job.get_id() << endl;
        // parse commands
        string open_symbol("{");
        string close_symbol("}");
        size_t open_pos = parts[1].find(open_symbol);
        size_t close_pos = parts[1].find(close_symbol);
        string commands = parts[1].substr(open_pos + 1,
            close_pos - open_pos - 1);
        size_t nl_pos = 0;
        while ((nl_pos = commands.find('\n')) != string::npos) {
            string cmd_line = commands.substr(0, nl_pos);
            trim(cmd_line);
            if (cmd_line.length() != 0) {
                job.add_command(cmd_line);
            }
            commands.erase(0, nl_pos + 1);
        }
        cerr << job.get_command_size() << endl;



        job_defs.erase(0, end_pos + end_symbol.length());
    }

    // parse alias section

    // parse instance section

    return true;
}
