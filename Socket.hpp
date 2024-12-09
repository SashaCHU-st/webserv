#pragma once
#include <sys/wait.h>
#include <netinet/in.h>
#include "stdio.h"
#include <iostream>
#include <sys/socket.h>
class Socket
{
    private:
        int sock;
        int conn;
        struct sockaddr_in address;
    public:
        Socket(int domain, int service, int protocol, int port, u_long interface);
        int getconn();
        struct sockaddr_in getsockaddr_in_address();
        int getsock();
        virtual int establish_network(int sock, struct sockaddr_in address) = 0;
        void test_conn(int);
};