/// not yet ready for now!!!!!
///Function to conncet. From Client to server. Takes fd from socket, pointer to struct containing
// IP address to BIND soket to, adrlen => the size of adress structure
#include "Connecting_from_client.hpp"

//conctr
Connecting_from_client::Connecting_from_client(int domain, int type, int protocol, u_long interface, int port)
    : Socket(domain, type, protocol, interface, port)
    {
    struct sockaddr_in address = get_address();
    std::cout<<"EEEEEEEEEEEEEEEEEEEEEE"<<std::endl;
    int connection = connect(get_sock(), (struct sockaddr *)&address, sizeof(address));
    if(connection < 0)
     {
        perror("failed");
        exit(EXIT_FAILURE);
    }  
    set_conn(connection);
    if (get_conn() < 0)
    {
        perror("failed");
        exit(EXIT_FAILURE);
    }
}
