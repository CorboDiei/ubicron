// Copyright 2021 David Corbo

#ifndef JOBS_H_
#define JOBS_H_

#include <cstdint>
#include <vector>
#include <queue>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

using namespace std;
using namespace boost::uuids;

// The entire list of jobs that the program

class Job {
    public:
        explicit Job(void) { }
        explicit Job(uuid id) : job_id_(id) { }
        // explicit Job(uuid )


        uuid get_id(void) {return job_id_;}
    private:
        uuid job_id_;



};

class InputJSON {
    public: 

    private: 

};

class OutputJSON {
    public: 

    private: 
};

class SubsequentJSON {
    public: 

    private: 
};

enum Instancetype { upon, every };

class Instance {
    public: 

    private:

};

class Jobs {
    public: 

    private:
        vector<Job> jobs_list_;
        vector<Instance> listeners_;
        queue<Instance> job_instances_;
};


#endif  // JOBS_H_