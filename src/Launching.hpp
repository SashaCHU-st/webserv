#pragma once
#include "Server.hpp"
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <poll.h>
#include <unistd.h>
#include <vector>

class Launching: public Server
{
    private:
        char buffer[30000] = {0};
        int new_socket;
        void accepter();
        void handler();
        void responder();
        std::vector<pollfd> fds;// for dinamicaly array of fd's
    public:
        Launching();
        void launch();
        int get_ret();
}; 