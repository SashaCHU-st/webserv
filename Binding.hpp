#pragma once
#include "Socket.hpp"

class Binding : public Socket
{
    public:
        Binding(int domain, int service, int protocol, u_long interface, int port);
        int establish_network(int sock, struct sockaddr_in address);
};