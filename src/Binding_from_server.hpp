#pragma once
#include "Socket.hpp"
 
class Binding_from_server : public Socket
{
    public:
        //constructors
        Binding_from_server(int domain, int type, int protocol, u_long interface, int port);
};