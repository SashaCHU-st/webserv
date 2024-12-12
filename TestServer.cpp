#include "TestServer.hpp"

TestServer::TestServer() : Server(AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY, 10)
{
    launch();
}

void TestServer::accepter()
{
    struct sockaddr_in address = get_socket()->get_address();
    int adrlen = sizeof(address);
    std::cout<<"111"<<std::endl;
    new_socket = accept(get_socket()->get_sock(), (struct sockaddr*)&address, (socklen_t *)&adrlen);
    std::cout<<"222"<<std::endl;

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

// void TestServer::responder()
// {
//     char *hello = "hellooooo";
//     write(new_socket, hello, strlen(hello));
//     close(new_socket);
// }
void TestServer::responder()
{
    const char* http_response = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 12\r\n"
        "\r\n"
        "Hello World!";
    write(new_socket, http_response, strlen(http_response));
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