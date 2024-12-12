#pragma once
#include "Socket.hpp"
 
class ConnectingSocket : public Socket
{
    public:
        ConnectingSocket(int domain, int type, int protocol, u_long interface, int port, int backlog);
        int establish_network(int sock, struct sockaddr_in address);
}; 