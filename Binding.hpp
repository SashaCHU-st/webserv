#pragma once
#include "Socket.hpp"

class Binding : public Socket
{
    public:
        Binding(int domain, int service, int port, int protocol, u_long interface) : Socket(domain, service, protocol,port, interface){};
        int connect(int sock, struct sockaddr_in address);
};