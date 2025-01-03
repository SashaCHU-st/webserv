#include "WebServ.hpp"

void WebServ::set_non_blocking(int sock_fd)
{
   // fcntl(int fd, int cmd, and othe diff arguments);
    int non_block = fcntl(sock_fd, F_GETFL, 0);// checking the access to socket, 
    // if it is < 0 then fcnl failed
    if (non_block < 0)
    {
        perror("fcntl get failed");
        exit(EXIT_FAILURE);
    }
    if (fcntl(sock_fd, F_SETFL, non_block | O_NONBLOCK) < 0)// makes socket non blocking by
    // O_NONBLOCK flag
    // F_SETFL 
    {
        perror("fcntl set non-blocking failed");
        exit(EXIT_FAILURE);
    }
}

WebServ::WebServ(int domain, int type, int protocol, int port, u_long interface, int backlog)
    : Server(domain, type, protocol, port, interface, backlog) {}

void WebServ::accepter() {
  //  std::cout << "Accepter" << std::endl;

    Socket* socket = get_sock();
    if (socket == nullptr)
        return;

    int sock_fd = socket->get_sock();
    if (sock_fd < 0)
        return;

    struct sockaddr_in address = socket->get_address();
    socklen_t adrlen = sizeof(address);
    _new_socket = accept(sock_fd, (struct sockaddr*)&address, &adrlen);
    // listen socket to accept incom conn req from CLIENT
    // creates newsocket and return a fd for new socket
    // the original "big socket" will remain open and contuue listen for new incomes

    if (_new_socket < 0)
    {
        if (errno == EWOULDBLOCK || errno == EAGAIN)
            std::cout << "No pending connections. Non-blocking accept returned." << std::endl;
        else
            perror("Failed to accept connection");
        return;
    }

    set_non_blocking(_new_socket); // new sockecke to non blocking
    std::cout << "Connection accepted, FD: " << _new_socket << std::endl;

}





std::vector<pollfd> *WebServ::get_fds()
{
	return &fds;
}



void WebServ::responder(int client_fd)
{
    std::ifstream file("index1.html");
    if (!file.is_open()) {
        std::string error_response =
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: 0\r\n"
            "\r\n";
        write(client_fd, error_response.c_str(), error_response.size());
        close(client_fd);
        return;
    }

    // not sure what is taht but it is working
    std::ostringstream ss;
    ss << file.rdbuf();
    std::string body = ss.str();
    file.close();

    std::string http_response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: " + std::to_string(body.size()) + "\r\n"
        "\r\n" +
        body;

    // Send the response
    ssize_t bytes_written = 0;
    ssize_t total_bytes = http_response.size();
    while (bytes_written < total_bytes)
    {
        ssize_t current_write = write(client_fd, http_response.c_str() + bytes_written, total_bytes - bytes_written);
        if (current_write < 0)
        {
            perror("Write failed");
            close(client_fd);
            return;
        }
        bytes_written += current_write;
    }

    std::cout << "Response to client FD: " << client_fd << std::endl;
    close(client_fd); 
}

void WebServ::launch(int nums)
{
    std::vector<pollfd> fds;
    std::vector<WebServ*> servers;

    // Creating mult servers for now 3, as set in main
    for (int i = 0; i < nums; ++i)
    {
        int port = 4051 + i;
        WebServ* server = new WebServ(AF_INET, SOCK_STREAM, 0, port, INADDR_ANY, 32);
        servers.push_back(server);

        pollfd server_poll;
        server_poll.fd = server->get_sock()->get_sock(); 
        server_poll.events = POLLIN;
        fds.push_back(server_poll);

        std::cout << "Port: " << port << std::endl;
    }
/////POLL loop
    while (true)
    {
        int polling_result = poll(fds.data(), fds.size(), -1);// -1 no timeout for now

        if (polling_result < 0) {
            perror("Poll failed");
            exit(EXIT_FAILURE);
        }
        std::cout << "Active FDs: " << polling_result << std::endl;/// not need later

        for (size_t i = 0; i < fds.size(); ++i)
        {
            if (fds[i].revents & POLLIN)
            {
                std::cout << "POLLIN  on FD: " << fds[i].fd << std::endl;
                bool is_server_socket = false;
                for (size_t j = 0; j < servers.size(); ++j)
                {
                    if (fds[i].fd == servers[j]->get_sock()->get_sock())
                    {
                        servers[j]->accepter(); // Accept a new connection and creating _new_socket
                        pollfd client_poll;
                        client_poll.fd = servers[j]->_new_socket;
                        client_poll.events = POLLIN;
                        fds.push_back(client_poll);
                        std::cout << "!!!!New client FD added to poll: " << servers[j]->_new_socket << std::endl;
                        is_server_socket = true;
                        break;
                    }
                }
                // Client socket: Respond to the client
                if (!is_server_socket) {
              //      std::cout << "Client FD: " << fds[i].fd << " - Calling responder()" << std::endl;
                    responder(fds[i].fd);
                    close(fds[i].fd);
                    fds.erase(fds.begin() + i);
                    --i;
                }
            }
            if (fds[i].revents & (POLLHUP | POLLERR))
            {
                std::cout << "POLLHUP or POLLERR detected on FD: " << fds[i].fd << std::endl;
                close(fds[i].fd);
                fds.erase(fds.begin() + i); 
                --i; 
            }
        }
    }

}
