#pragma once

#include "Server.hpp"
#include "ParseConfig.hpp"
#include <fcntl.h>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <poll.h>

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
    void responder(int client_fd);
    void launch(int nums);
    void set_non_blocking(int sock_fd);
    std::vector<pollfd> *get_fds();
};
