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
        Socket(int domain, int service, int protocol,u_long interface, int port);
        int get_conn();
        struct sockaddr_in get_address();
        int get_sock();
        virtual int establish_network(int sock, struct sockaddr_in address) = 0;
        void test_conn(int);
        void set_conn(int conn);
}; 