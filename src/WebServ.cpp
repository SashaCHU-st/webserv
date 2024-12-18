#include "WebServ.hpp"

// WebServ::WebServ() : Server(AF_INET, SOCK_STREAM, 0, 8083, INADDR_ANY, 32)
// {

// }
WebServ::WebServ(int domain, int type, int protocol, int port, u_long interface, int backlog)
    : Server(domain, type, protocol, port, interface, backlog) {}

void WebServ::accepter()
{
    struct sockaddr_in address = get_sock()->get_address();
    socklen_t adrlen = sizeof(address);
    _new_socket = accept(get_sock()->get_sock(), (struct sockaddr*)&address, &adrlen);
    if (_new_socket < 0)
    {
        perror("Failed");
        exit(EXIT_FAILURE);
    }
            std::cout << "\033[34mAll good\033[0m" << std::endl;
    // memset(buffer, 0, sizeof(buffer));
    // int reading = read(_new_socket, buffer, sizeof(buffer) - 1);
    // if (reading < 0)
    // {
    //     perror("Failed");
    //     close(_new_socket);
    // }
}

// Prints the received request
// void WebServ::handler()
// {
//     std::cout << buffer << std::endl;
// }

// Sends a response to the client

std::vector<pollfd> *WebServ::get_fds()
{
	return &fds;
}
void WebServ::responder()
{
    std::string body;
    std::ifstream file("www/index1.html"); // Open the file
    if (file.is_open())
    {
        std::ostringstream ss;
        ss << file.rdbuf(); 
        body = ss.str();
        file.close();
    }

    // Construct HTTP response
    std::string http_response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: " +
        std::to_string(body.size()) + "\r\n"
        "\r\n" +
        body;
    int writing = write(_new_socket, http_response.c_str(), http_response.size());
    if (writing < 0)
    {
        perror("Failed");
    }
    close(_new_socket);
}

// Main server loop
void WebServ::launch()
{
    while (true)
    {
        std::cout << "\033[31mLet's start\033[0m" << std::endl;
         struct pollfd creating_serv;
        creating_serv.fd = sock;
        creating_serv.events = POLLIN;
        fds.push_back(creating_serv);
        std::cout<<"4"<<std::endl;
        int polling = poll(fds.data(), fds.size(),30 *1000);
        std::cout<<"POLLL "<< polling<<std::endl; 
        std::cout<<"5"<<std::endl; 
        if(polling < 0)
        {
            perror("failed");
            exit(EXIT_FAILURE);
        }
        accepter();
        responder();
        std::cout << "\033[32mVery good\033[0m" << std::endl;
    }
}
