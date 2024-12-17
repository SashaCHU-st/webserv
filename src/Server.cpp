#include "Server.hpp"

Server::Server(int domain, int type, int protocol, int port, u_long interface, int backlog)
{
    sock = new Socket(domain, type, protocol, interface, port, backlog);
}

Socket* Server::get_sock()
{
    return (sock);
}
