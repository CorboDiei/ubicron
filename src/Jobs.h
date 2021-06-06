// Copyright 2021 David Corbo

#ifndef JOBS_H_
#define JOBS_H_

#include <cstdint>
#include <vector>
#include <queue>
#include <string>
#include <map>
// #include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "./thirdparty/boost/uuid/uuid.hpp"
#include "./thirdparty/json.hpp"

using namespace std;
using namespace boost::uuids;
using json = nlohmann::json;

enum FormatType { unset, input, output, sub_triggers };

class FormatTree {
    public:
        FormatTree(void) : type_(FormatType::unset) { }
        explicit FormatTree(string json_text);

        bool verify_tree(FormatType type);

        string get_value(string query);

    private:
        json tree_;
        FormatType type_;
};

class Job {
    public:
        // ctors
        Job(void) : verified_(false) { }
        explicit Job(uuid id) : job_id_(id), verified_(false) { }
        explicit Job(uuid id, vector<string> commands,
            FormatTree input, FormatTree output, FormatTree sub_trigs);
        // dtor
        ~Job(void) { }

        // getters and setters
        uuid get_id(void) { return job_id_; }
        void set_id(uuid id) { job_id_ = id; }
        vector<string> get_commands(void) { return commands_; }
        string get_next_command(void);
        bool set_commands(vector<string> commands);
        bool add_command(string command);
        FormatTree get_input(void) { return input_; }
        bool set_input(FormatTree input);
        FormatTree get_output(void) { return output_; }
        bool set_output(FormatTree output);
        FormatTree get_sub_trigs(void) { return sub_triggers_; }
        bool set_sub_trigs(FormatTree sub_trigs);

        int get_command_size(void) { return commands_.size(); }
        bool is_verified(void) { return verified_; }
    private:
        uuid job_id_;
        vector<string> commands_;
        FormatTree input_, output_, sub_triggers_;
        unsigned int on_command_;
        bool verified_;
};

enum Instancetype { upon, every };

class Instance {
    public:
        Instance(void) { }

    private:
        Instancetype type_;

};

class Jobs {
    public:
        // ctors
        Jobs(void) : verified_(false) { }
        // dtor
        ~Jobs(void) { }



    private:
        map<uuid, Job> jobs_list_;
        map<string, uuid> aliases_;
        vector<Instance> listeners_;
        queue<Instance> job_instances_;
        bool verified_;
};


#endif  // JOBS_H_