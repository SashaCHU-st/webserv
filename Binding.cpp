#include "Binding.hpp"
//conctr 
Binding::Binding(int domain, int service, int protocol, u_long interface, int port)
    : Socket(domain, service, protocol, interface, port) {
    set_conn(establish_network(get_sock(), get_address()));
    test_conn(get_conn());
}
//implement of conn
int Binding::establish_network(int sock, struct sockaddr_in address)
{
    return bind(sock, (struct sockaddr *)&address, sizeof(address));
    // casting address to a strcut * and making it a pointer
};