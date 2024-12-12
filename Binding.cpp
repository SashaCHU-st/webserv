#include "Binding.hpp"
//conctr 
Binding::Binding(int domain, int type, int protocol, u_long interface, int port)
    : Socket(domain, type, protocol, interface, port) {
    set_conn(establish_network(get_sock(), get_address()));
    if(get_conn() < 0)
    {
        perror("failed");
        exit(EXIT_FAILURE);
    }
}
//implement of conn
int Binding::establish_network(int sock, struct sockaddr_in address)
{
    return bind(sock, (struct sockaddr *)&address, sizeof(address));
    // casting address to a strcut * and making it a pointer
};