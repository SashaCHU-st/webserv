#pragma once

#include "Server.hpp"
#include <fstream>
#include <sstream>
#include <cstring>

class WebServ : public Server
{
private:
    int new_socket;          // Socket for the accepted client connection
    char buffer[30000];      // Buffer to store client request
//       std::vector<pollfd> fds;// for dinamicaly array of fd's

public:
    WebServ();
    void accepter();
    void handler();
    void responder();
    void launch();           
};
