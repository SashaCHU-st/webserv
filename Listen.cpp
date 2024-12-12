#include "Listen.hpp"

Listen::Listen(int domain, int service, int protocol, int port, u_long interface, int backlog) 
: Binding(domain, service, protocol, interface, port)
{
    backlog = backlog;
    start_listen();
    std::cout << "3" <<std::endl;
    test_conn(listening);
}; 

void Listen::start_listen()
{
    std::cout << "1" <<std::endl;
    std::cout << get_conn() <<std::endl;
    listening =  listen(get_sock(), backlog );
    std::cout << "2" <<std::endl;
} 