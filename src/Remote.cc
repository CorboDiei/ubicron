// Copyright 2021 David Corbo

#include "./Remote.h"
#include "./Jobs.h"

bool Remote::full_connection(void) {
    short portnum;
    int fd;
    if (!establish_connection(&portnum, &fd)) {
        return false;
    }
    if (!handshake()) {
        return false;
    }
    return true;
}

bool Remote::establish_connection(short* port, int* fd) {
    return true;
}

bool Remote::handshake(void) {
    return true;
}

bool Remote::load_remote_jobs(map<string, FormatTree>* remote_list) {
    // parse the input from the server, loading the aliases and
    // input formats into the arg
    return true;
}
bool Remote::daemonize(void) {
    return true;
}