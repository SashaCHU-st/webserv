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
        struct pollfd client_poll;
    client_poll.fd = _new_socket;
    client_poll.events = POLLIN;
    fds.push_back(client_poll);
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
void WebServ::responder(int client_fd)
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
    int writing = write(client_fd, http_response.c_str(), http_response.size());
    if (writing < 0)
    {
        perror("Failed");
    }
    close(client_fd);
}


void WebServ::launch()
{
    struct pollfd server_poll;
    server_poll.fd = get_sock()->get_sock();
    server_poll.events = POLLIN;
    fds.push_back(server_poll);

    while (true)
    {
        // std::cout << "\033[31mPolling \033[0m" << std::endl;
        // std::cout << "\033[31mSize \033[0m" << fds.size()<< std::endl;
        int polling = poll(fds.data(), fds.size(), 30*1000);
        if (polling < 0)
        {
            perror("Poll failed");
            exit(EXIT_FAILURE);
        }
        for (size_t i = 0; i < fds.size(); ++i)
        {
            if (fds[i].revents & POLLIN)// if revent POLLIN =>then data is aval 
            {
        // std::cout << "\033[31mData  \033[0m" << fds.data()<< std::endl;
                if (fds[i].fd == get_sock()->get_sock())/// if it is server's socket
                {
                    std::cout << "\033[34mIncoming \033[0m" << std::endl;
                    accepter();// accpet new connection
                } 
                else// if clinet socket
                {
                    std::cout << "\033[31m1 \033[0m" << fds.data()<< std::endl;
                    // responder();
                     responder(fds[i].fd);// if it is client socket then send response
                    close(fds[i].fd); // Закрываем соединение
                    fds.erase(fds.begin() + i); // Удаляем из списка
                    --i; // Корректируем индекс
                }
            }
            else if (fds[i].revents & POLLHUP || fds[i].revents & POLLERR)/// if revnt is "hangup detected" or "err occured"
            {
                 std::cout << "\033[31m2  \033[0m" << fds.data()<< std::endl;
                close(fds[i].fd);// close socket
                fds.erase(fds.begin() + i);// deleted socket from array's 
                --i;// delete index to contunue working with other sockets
                std::cout << "\033[33mClient disconnected\033[0m" << std::endl;
            }
        }
        // std::cout << "\033[32mReady for the next connection...\033[0m" << std::endl;
    }
}


