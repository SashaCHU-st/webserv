#include "Listen.hpp"

Listen::Listen(int domain, int type, int protocol, int port, u_long interface, int backlog) 
: Binding_from_server(domain, type, protocol, interface, port)
{
    backlog = get_backlog();
    listening = listen(get_sock(), backlog);
    if(listening < 0)
    {
        perror("failed");
        exit(EXIT_FAILURE);
    }
}; 

int Listen::get_backlog()
{
    return backlog;
}
