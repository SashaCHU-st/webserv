#include "Server.hpp"
#include "Listen.hpp"

Server::Server(int domain, int type, int protocol, int port,  u_long interface, int backlog  )
{
    socket = new Listen(domain, type, protocol, port, interface, backlog);

   // delete socket;// avoid memry leak

};

Listen * Server::get_socket()
{
    return socket;
} 