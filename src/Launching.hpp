#pragma once
#include "Server.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <fcntl.h>


class Launching: public Server
{
    private:
        char buffer[30000] = {0};
        int new_socket;
        void accepter();
        void handler();
        void responder();
    public:
        Launching();
        void launch();
}; 