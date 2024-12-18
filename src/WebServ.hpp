#pragma once

#include "Server.hpp"
#include <fstream>
#include <sstream>
#include <cstring>

class WebServ : public Server
{
private:
    int _new_socket;
 // char buffer[30000];
//  std::vector<pollfd> fds;// for dinamicaly array of fd's
    std::vector<struct pollfd> fds;/// for dinamcalyy fds

public:
     WebServ(int domain, int type, int protocol, int port, u_long interface, int backlog);
    void accepter();
    void responder();
    void launch();
    std::vector<pollfd> *get_fds();
};
