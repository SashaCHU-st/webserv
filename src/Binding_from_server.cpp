///Function to bind. From server to client. Takes fd from socket, pointer to struct containing
// IP address to BIND soket to, adrlen => the size of adress structure
#include "Binding_from_server.hpp"
Binding_from_server::Binding_from_server(int domain, int type, int protocol, u_long interface, int port)
    : Socket(domain, type, protocol, interface, port) {
    struct sockaddr_in address = get_address();
    int binding_from_server = bind(get_sock(), (struct sockaddr *)&address, sizeof(address));
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
