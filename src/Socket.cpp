#include "Socket.hpp"

// Constructor: Initializes socket details and creates the socket
Socket::Socket(int domain, int type, int protocol, u_long interface, int port, int backlog)
    : domain(domain), type(type), protocol(protocol), backlog(backlog)
{
    // Initialize the address structure
    address.sin_family = domain;          // AF_INET
    address.sin_port = htons(port);       // Port
    address.sin_addr.s_addr = htonl(interface); // INADDR_ANY (0.0.0.0)

    fds = new std::vector<struct pollfd>();

}

int Socket::get_conn()
{ 
    return conn;
}


int Socket::get_sock()
{
    return sock;
}


std::vector<pollfd> *Socket::get_fds()
{
	return fds;
}
struct sockaddr_in Socket::get_address()
{
    return address;
}

void Socket::set_conn(int conn)
{
    this->conn = conn;
}

void Socket::socketing()
{
    sock = socket(domain, type, protocol); // AF_INET, SOCK_STREAM, 0 ( 0 default based on type if SOCK_STREAM => TCP)
                                         //SOK_DGRAM =>UDP
    if (sock < 0)
    {
        perror("Failed");
        exit(EXIT_FAILURE);
    }
}
void Socket::binding()
{
    int binding_from_server = bind(get_sock(), (struct sockaddr *)&address, sizeof(address));
    std::cout<<"QQQQQQQQQQQ"<<std::endl;
    if(binding_from_server)
    {
        perror("failed");
        exit(EXIT_FAILURE);
    }
    set_conn(binding_from_server);
    if(get_conn() < 0)
    {
        perror("failed");
        exit(EXIT_FAILURE);
    }
}
void Socket::listening()
{
    int listening_status = listen(sock, backlog); // backlog is the max number of pending connections
    if (listening_status < 0)
    {
        perror("failed");
        exit(EXIT_FAILURE);
    }
}

void Socket::run(std::vector<pollfd> &fds)
{

    socketing();
    binding();
    listening();

    struct pollfd creating_serv;
    creating_serv.fd = sock;
    creating_serv.events = POLLIN;
    fds.push_back(creating_serv);
    int polling = poll(fds.data(), fds.size(),30 *1000);
    if(polling < 0)
    {
        perror("failed");
        exit(EXIT_FAILURE);
    }
}

