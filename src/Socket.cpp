#include "Socket.hpp"

Socket::Socket(int domain, int service, int protocol, u_long interface, int port)
{
    address.sin_family= domain;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(interface);
  sock = socket(domain, service, protocol);
  test_conn(sock);
//   conn = establish_network(sock, address);
//   test_conn(conn);
};

void Socket::test_conn(int item_to_test)
{
    if(item_to_test < 0)
    {
        perror("failed");
        exit(EXIT_FAILURE);
    }
    
}
int Socket::get_conn()
{ 
    return(conn);
};

int Socket::get_sock()
{
    return(sock);
};
struct sockaddr_in Socket::get_address()
{
    return(address);
};

void Socket::set_conn(int conn)
{
    conn = conn;
};