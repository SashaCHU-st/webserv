#include "Socket.hpp"

Socket::Socket(int domain, int type, int protocol, u_long interface, int port)
{
    address.sin_family= domain;// AF_INET
    address.sin_port = htons(port);// 8080
    address.sin_addr.s_addr = htonl(interface);//INADDR_ANY 0.0.0.0
    sock = socket(domain,type, protocol);// AF_INET, SOCK_STREAM, 0 ( 0 default based on type if SOCK_STREAM => TCP)
                                        //SOK_DGRAM =>UDP
    if(sock < 0)
    {
        perror("failed");
        exit(EXIT_FAILURE);
    }
};

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
    this->conn = conn;
};