#pragma once
#include "Socket.hpp"
 
class Connecting_from_client : public Socket
{
    public:
        Connecting_from_client(int domain, int type, int protocol, u_long interface, int port);
}; 