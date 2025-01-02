// #include "WebServ.hpp"

// WebServ::WebServ(int domain, int type, int protocol, int port, u_long interface, int backlog)
//     : Server(domain, type, protocol, port, interface, backlog) {}

// // void WebServ::accepter()
// // {
// //     struct sockaddr_in address = get_sock()->get_address();
// //     socklen_t adrlen = sizeof(address);
// //     _new_socket = accept(get_sock()->get_sock(), (struct sockaddr*)&address, &adrlen);/// check clinent connect mnd acept
// //     //accept new coming conn from client
// //     if (_new_socket < 0)
// //     {
// //         perror("Failed");
// //         exit(EXIT_FAILURE);
// //     }
// //     std::cout << "\033[34mAll good\033[0m" << std::endl;
// //     struct pollfd client_poll;// set pollfd stcrct that uses I/O in client socket
// //     client_poll.fd = _new_socket;// set fd for lient socket
// //     client_poll.events = POLLIN;//folowing only POLLIN events (=>data ready to read)
// //     fds.push_back(client_poll);/// adding client to list of sockets
// // }
// void WebServ::accepter()
// {
//     struct sockaddr_in client_addr;
//     socklen_t client_len = sizeof(client_addr);
//     _new_socket = accept(get_sock()->get_sock(), (struct sockaddr*)&client_addr, &client_len);  // Assign to _new_socket

//     if (_new_socket < 0)
//     {
//         perror("Failed to accept connection");
//         return;
//     }

//     std::cout << "New connection accepted: " << _new_socket << std::endl;

//     // Use _new_socket for further processing
//     pollfd client_poll;
//     client_poll.fd = _new_socket;
//     client_poll.events = POLLIN;
//     fds.push_back(client_poll);  // Add the client socket to the pollfd vector
// }




// std::vector<pollfd> *WebServ::get_fds()
// {
// 	return &fds;
// }
// void WebServ::responder(int client_fd)
// {
//     std::string body;
//     std::ifstream file("www/index1.html"); // Open the file
//     if (file.is_open())
//     {
//         std::ostringstream ss;
//         ss << file.rdbuf(); 
//         body = ss.str();
//         file.close();
//     }

//     // Construct HTTP response
//     std::string http_response =
//         "HTTP/1.1 200 OK\r\n"
//         "Content-Type: text/html\r\n"
//         "Content-Length: " +
//         std::to_string(body.size()) + "\r\n"
//         "\r\n" +
//         body;
//     int writing = write(client_fd, http_response.c_str(), http_response.size());
//     if (writing < 0)
//     {
//         perror("Failed");
//     }
//     close(client_fd);
// }



// void WebServ::launch(int nums)
// {
//     // pollfd server_poll;
//     // server_poll.fd = get_sock()->get_sock();// sock, fd od connection
//     // server_poll.events = POLLIN; // requested event ; revent =>returned event 0
//     // fds.push_back(server_poll);
//     std::vector<WebServ*> servers; // A vector to store dynamically allocated WebServ objects
//     std::vector<pollfd> poll_fds;  // Vector to store pollfd structures

//     // Dynamically create servers
//     for (int i = 0; i < nums; ++i)
//     {
//         int port = 3000 + i;  // Each server gets a port starting from 3000
//         WebServ* server = new WebServ(AF_INET, SOCK_STREAM, 0, port, INADDR_ANY, 32);
//         servers.push_back(server);

//         pollfd server_poll;
//         server_poll.fd = server->get_sock()->get_sock();
//         server_poll.events = POLLIN;
//         poll_fds.push_back(server_poll);
//     }

//     while (true)
//     {
//         // std::cout << "\033[31mPolling \033[0m" << std::endl;
//         int polling = poll(fds.data(), fds.size(), 30*1000);// if -1 blocking function 
//         std::cout << "\033[31mSize \033[0m" << fds.size()<< std::endl;
//         if (polling < 0)
//         {
//             perror("Poll failed");
//             exit(EXIT_FAILURE);
//         }
//         for (size_t i = 0; i < fds.size(); ++i)
//         {
//             if (fds[i].revents & POLLIN)// if revent POLLIN =>then data is aval 
//             {
//                 if (fds[i].fd == get_sock()->get_sock())/// if it is server's socket
//                 {
//                     std::cout << "\033[34mIncoming \033[0m" << std::endl;
//                     accepter();// accpet new connection
//                 } 
//                 else// if clinet socket
//                 {
//                     std::cout << "\033[31m1 \033[0m" << fds.data()<< std::endl;
//                     responder(fds[i].fd);// if it is client socket then send response
//                     close(fds[i].fd); // close conn
//                     fds.erase(fds.begin() + i); // delete from array
//                     --i; // changing o proper index
//                 }
//             }
//             else if (fds[i].revents & POLLHUP || fds[i].revents & POLLERR)/// if revnt is "hangup detected" or "err occured"
//             {
//                  std::cout << "\033[31m2  \033[0m" << fds.data()<< std::endl;
//                 close(fds[i].fd);// close socket
//                 fds.erase(fds.begin() + i);// deleted socket from array's 
//                 --i;// delete index to contunue working with other sockets
//                 std::cout << "\033[33mClient disconnected\033[0m" << std::endl;
//             }
//         }
//         // std::cout << "\033[32mReady for the next connection...\033[0m" << std::endl;
//     }
// }

// // void WebServ::responder(int client_fd)
// // {
// //     std::string body;
// //     std::ifstream file("www/index1.html"); //
// //     if (file.is_open())
// //     {
// //         std::ostringstream ss;
// //         ss << file.rdbuf(); // !!!!!!!!!!!
// //         body = ss.str();
// //         file.close();
// //         std::cout << "size: " << body.size() << " bytes" << std::endl;
// //     }
// //     else
// //     {
// //         std::string error_response = 
// //             "HTTP/1.1 404 Not Found\r\n"
// //             "Content-Type: text/html\r\n"
// //             "Content-Length: 0\r\n"
// //             "\r\n";
// //         write(client_fd, error_response.c_str(), error_response.size());
// //         close(client_fd);
// //         return;
// //     }
// //     std::string http_response =
// //         "HTTP/1.1 200 OK\r\n"
// //         "Content-Type: text/html\r\n"
// //         "Content-Length: " + std::to_string(body.size()) + "\r\n"
// //         "\r\n" + body;
// //     ssize_t bytes_written = 0;
// //     size_t total_bytes = body.size();
// //     while (bytes_written < static_cast<ssize_t>(total_bytes))
// //     {
// //         ssize_t current_write = write(client_fd, http_response.c_str() + bytes_written, total_bytes - bytes_written);
// //         if (current_write < 0)
// //         {
// //             perror("write failed");
// //             close(client_fd);
// //             return;
// //         }
// //         bytes_written += current_write;
// //     }

// //     std::cout << "Response sent successfully." << std::endl;
// //     close(client_fd);
// // }




// // void WebServ::launch(int nums)
// // {
// //     std::vector<pollfd> fds;
// //     std::vector<WebServ*> servers;
// //     for (int i = 0; i < nums; ++i)
// //     {
// //         int port = 3000 + i;  // starts from 300 FOR NOW
// //         WebServ* server = new WebServ(AF_INET, SOCK_STREAM, 0, port, INADDR_ANY, 32);
// //         servers.push_back(server);

// //         pollfd server_poll;
// //         server_poll.fd = server->get_sock()->get_sock(); 
// //         server_poll.events = POLLIN;  // for pollin events
// //         fds.push_back(server_poll);

// //         std::cout << "Starting server on port: " << port << std::endl;
// //     }

// //     //For multiple connections
// //     while (true)
// //     {
// //         int polling_result = poll(fds.data(), fds.size(), -1);  

// //         if (polling_result < 0)
// //         {
// //             perror("Poll failed");
// //             exit(EXIT_FAILURE);
// //         }
// //         for (size_t i = 0; i < fds.size(); ++i)
// //         {
// //             if (fds[i].revents & POLLIN) 
// //             {
// //                 if (fds[i].fd == servers[i]->get_sock()->get_sock()) 
// //                 {
// //                     std::cout << "Incoming connection on server FD: " << fds[i].fd << std::endl;
// //                     servers[i]->accepter();
// //                 }
// //                 else 
// //                 {
// //                     std::cout << "Handling client FD: " << fds[i].fd << std::endl;
// //                     servers[i]->responder(fds[i].fd); 
// //                     close(fds[i].fd); 
// //                     fds.erase(fds.begin() + i);
// //                     --i;
// //                 }
// //             }
// //             else if (fds[i].revents & (POLLHUP | POLLERR))  // Handle errors or hangup
// //             {
// //                 std::cout << "Error or client disconnected on FD: " << fds[i].fd << std::endl;
// //                 close(fds[i].fd);
// //                 fds.erase(fds.begin() + i);
// //                 --i;
// //             }
// //         }
// //     }
// // }
// // ////////////////////////////////////////////////////////////////////////////////////////////////