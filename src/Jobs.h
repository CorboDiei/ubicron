// Copyright 2021 David Corbo

#ifndef JOBS_H_
#define JOBS_H_

#include <cstdint>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/property_tree/json_parser.hpp>


using namespace std;
using namespace boost::uuids;
namespace pt = boost::property_tree;

enum FormatType { input, output, sub_triggers };

class FormatTree {
    public:
        explicit FormatTree(string json_text);

        bool verify_tree(FormatType type);

        string get_value(string query);

    private:
        pt::ptree root;
        FormatType type_;
};

class Job {
    public:
        Job(void) { }
        explicit Job(uuid id) : job_id_(id) { }
        explicit Job(uuid id, vector<string> commands,
            FormatTree input, FormatTree output, FormatTree sub_trigs);

        uuid get_id(void) {return job_id_;}
    private:
        uuid job_id_;
        vector<string> commands;



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