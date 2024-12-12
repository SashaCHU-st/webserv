#include "Listen.hpp"

Listen::Listen(int domain, int type, int protocol, int port, u_long interface, int backlog) 
: Binding(domain, type, protocol, interface, port)
{
    backlog = backlog;
    start_listen();
    std::cout << "3" <<std::endl;
    if(listening < 0)
    {
        perror("failed");
        exit(EXIT_FAILURE);
    }
}; 

void Listen::start_listen()
{
    std::cout << "1" <<std::endl;
    std::cout << get_conn() <<std::endl;
    listening =  listen(get_sock(), backlog );
    std::cout << "2" <<std::endl;
} 