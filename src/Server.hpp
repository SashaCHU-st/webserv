#pragma once
#include "Socket.hpp"

class Server 
{
    private:
        Socket* sock; 
        virtual void accepter() = 0;
        virtual void responder(int client_fd) = 0;
    public:
        Server(int domain, int type, int protocol, int port, u_long interface, int backlog);
        virtual ~Server();
        virtual void launch(int nums) = 0;
        Socket * get_sock();

}; 