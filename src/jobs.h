// Copyright 2021 David Corbo

#ifndef JOBS_H_
#define JOBS_H_

#include <cstdint>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

// The entire list of jobs that the program

class jobs {
    public: 

    private:
        vector<job> jobs_list_;
        vector<instance> listeners_;
        queue<instance> job_instances_;
};

class job {
    public:

    private:
        uint64_t job_uuid_;



};

class inputJSON {
    public: 

    private: 

};

class outputJSON {
    public: 

    private: 
};

class subsequentJSON {
    public: 

    private: 
};

enum instancetype { upon, every };

class instance {
    public: 

    private:

};


#endif  // JOBS_H_