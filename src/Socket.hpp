#pragma once
#include <sys/wait.h>
#include <netinet/in.h>
#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
class Socket
{
    private:
        int sock;
        int conn;
        struct sockaddr_in address;
    public:
        // constructors
        Socket(int domain, int type, int protocol,u_long interface, int port);
        //getters
        struct sockaddr_in get_address();
        int get_sock();
        int get_conn();

        //setters
        void set_conn(int conn);
}; 