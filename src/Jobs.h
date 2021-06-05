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
        json tree;
        FormatType type_;
};

class Job {
    public:
        Job(void) : verified_(false) { }
        explicit Job(uuid id) : job_id_(id), verified_(false) { }
        explicit Job(uuid id, vector<string> commands,
            FormatTree input, FormatTree output, FormatTree sub_trigs);

        uuid get_id(void);
        bool set_id(uuid id);

        FormatTree get_input(void) {return input_;}

    private:
        uuid job_id_;
        vector<string> commands_;
        FormatTree input_, output_, sub_triggers_;
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

    private:
        map<uuid, Job> jobs_list_;
        map<string, uuid> aliases_;
        vector<Instance> listeners_;
        queue<Instance> job_instances_;
};


#endif  // JOBS_H_