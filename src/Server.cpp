#include "Server.hpp"

Server::Server(int domain, int type, int protocol, int port, u_long interface, int backlog)
{
    sock = new Socket(domain, type, protocol, interface, port, backlog);

    if (!sock)
        exit(EXIT_FAILURE);

    if (sock->get_sock() < 0)
        exit(EXIT_FAILURE);
}



Server::~Server()
{
    delete sock;
}

Socket* Server::get_sock()
{
    if (sock == nullptr)
        exit(EXIT_FAILURE);  // if socket is invalid
    return sock;
}
