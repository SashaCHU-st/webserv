#include "Launching.hpp"

Launching::Launching() : Server(AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY, 32)
{
    launch();
}

void Launching::accepter()
{
    struct sockaddr_in address = get_socket()->get_address();
    int adrlen = sizeof(address);
    new_socket = accept(get_socket()->get_sock(), (struct sockaddr*)&address, (socklen_t *)&adrlen);
    if (new_socket < 0) {
        perror("failed");
        exit(EXIT_FAILURE);
    }
    read(new_socket, buffer, 30000);
}

void Launching::handler()
{
    std::cout << buffer << std::endl;
    
}

void Launching::responder()
{
    std::string body;
	std::ifstream file("index.html");
	if (file.is_open())
	{
		std::ostringstream ss;
		ss << file.rdbuf();
		body = ss.str();
		file.close();
	}

    std::string http_response = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: " + std::to_string(body.size()) + "\r\n"
        "\r\n" +
        body;
    write(new_socket, http_response.c_str(), http_response.size());
    close(new_socket);
}

void Launching::launch()
{
    while (true)
    {
        std::cout<<"Let;s start"<<std::endl;
        accepter();
        handler();
        responder();
        std::cout<<"all goood"<<std::endl;
    }
    
}