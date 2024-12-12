#include "ConnectingSocket.hpp"

//conctr
ConnectingSocket::ConnectingSocket(int domain, int type, int protocol, u_long interface, int port, int backlog)
    : Socket(domain, type, protocol, interface, port)
    {
    int connection = establish_network(get_sock(), get_address());// socket fd, sctryct adress
    set_conn(connection);
    if (get_conn() < 0)
    {
        perror("failed");
        exit(EXIT_FAILURE);
    }
}
//implement of conn
int ConnectingSocket::establish_network(int sock, struct sockaddr_in address)
{
    int hoho = connect(sock, (struct sockaddr *)&address, sizeof(address));
    if(hoho)
     {
        perror("failed");
        exit(EXIT_FAILURE);
    }  
    return hoho;
    // casting address to a strcut * and making it a pointer
};   