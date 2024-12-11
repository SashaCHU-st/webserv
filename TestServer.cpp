#include "TestServer.hpp"

TestServer::TestServer() : Server(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10)
{
    launch();
}

void TestServer::accepter()
{
    struct sockaddr_in address = get_socket()->getsockaddr_in_address();
    int adrlen = sizeof(address);
    new_socket = accept(get_socket()->get_sock(), (struct sockaddr*)&address, (socklen_t *)&adrlen);
    std::cout<<new_socket<<std::endl;
    if (new_socket < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    read(new_socket, buffer, 30000);
}

void TestServer::handler()
{
    std::cout << buffer<< std::endl;
}

void TestServer::responder()
{
    char *hello = "hellooooo";
    write(new_socket, hello, strlen(hello));
    close(new_socket);
}

void TestServer::launch()
{
    while (true)
    {
        std::cout<<"WAITING"<<std::endl;
        accepter();
        handler();
        responder();
        std::cout<<"all goood"<<std::endl;
    }
    
}