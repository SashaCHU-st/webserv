#pragma once
#include "Listen.hpp"

class Server 
{
    private:
        Listen * socket;
        virtual void accepter() = 0;
        virtual void handler() = 0;
        virtual void responder() = 0;
    public:
        Server(int damin, int service, int rotocol, int port, u_long interface, int backlog);
        virtual void launch() = 0;
        Listen * get_socket();

};