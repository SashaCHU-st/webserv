#include "ConnectingSocket.hpp"

//conctr
ConnectingSocket::ConnectingSocket(int domain, int service, int protocol, u_long interface, int port, int backlog)
    : Socket(domain, service, protocol, interface, port) {
    set_conn(establish_network(get_sock(), getsockaddr_in_address()));
    test_conn(get_conn());
}
//implement of conn
int ConnectingSocket::establish_network(int sock, struct sockaddr_in address)
{
    return connect(sock, (struct sockaddr *)&address, sizeof(address));
    // casting address to a strcut * and making it a pointer
};