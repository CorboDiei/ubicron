// Copyright 2021 David Corbo

#ifndef REMOTE_H_
#define REMOTE_H_

#include "./Jobs.h"


class Remote {
    public:
        bool full_connection(void);
        bool establish_connection(short* port, int* fd);
        bool handshake(void);
        bool load_remote_jobs(map<string, FormatTree>* remote_list);
        bool daemonize(void);
    private:
        short port_num;
        int fd;
};


#endif  // REMOTE_H_