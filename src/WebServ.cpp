#include "WebServ.hpp"

WebServ::WebServ() : Server(AF_INET, SOCK_STREAM, 0, 8081, INADDR_ANY, 32)
{
    launch();
}

void WebServ::accepter()
{
    struct sockaddr_in address = get_sock()->get_address();
    socklen_t adrlen = sizeof(address);
    new_socket = accept(get_sock()->get_sock(), (struct sockaddr*)&address, &adrlen);
    if (new_socket < 0)
    {
        perror("Failed");
        exit(EXIT_FAILURE);
    }
    std::cout << "All good" << std::endl;
    memset(buffer, 0, sizeof(buffer));    // Clear buffer before reading
    int reading = read(new_socket, buffer, sizeof(buffer) - 1);
    if (reading < 0)
    {
        perror("Failed");
        close(new_socket);
    }
}

// Prints the received request
void WebServ::handler()
{
    std::cout << buffer << std::endl;
}

// Sends a response to the client
void WebServ::responder()
{
    std::string body;
    std::ifstream file("index.html"); // Open the file
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
    int writing = write(new_socket, http_response.c_str(), http_response.size());
    if (writing < 0)
    {
        perror("Failed");
    }
    close(new_socket);
}

// Main server loop
void WebServ::launch()
{
    while (true)
    {
        std::cout << "Let's start" << std::endl;
        accepter();
        handler();
        responder();

        std::cout << "Very good\n" << std::endl;
    }
}
