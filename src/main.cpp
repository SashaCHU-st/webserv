/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:28:41 by alli              #+#    #+#             */
/*   Updated: 2025/01/03 10:00:36 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "Launching.hpp"

// // int main(int argc, char **argv)
// // {
// // 	std::string configFile = "test.conf";

// //     try {
// // 		if (argc == 2)
// // 		{
// // 			ParseConfig::splitConfigElements(configFile);
// // 		}
// //     	Launching webserv;
// //     }
// //     catch(std::exception& e)
// //     {
// //         std::cout << e.what() << std::endl;
// //         return 1;
// //     }
// //     return 0;
// // }
// int main(int argc, char **argv)
// {
// 	ParseConfig config;
// 	if (argc == 2)
// 	{
// 		std::string	file = argv[1];
// 		config.splitConfigElements(file);
// 	}
#include "WebServ.hpp"
#include "Signal.hpp"
#include "ParseConfig.hpp"

// void signalHandler(int signal) {
//     std::cerr << "signal: " << signal << std::endl;
//     exit(signal);
// }

int main(int argc, char **argv)
{ 
    // signal(SIGSEGV, signalHandler); // Seg  == 11
    // signal(SIGINT, signalHandler); // Ctrl+C == 2
    // signal(SIGTERM, signalHandler); // Termin
    Signal sig;

    (void)argv;
    (void) argc;
    try{
     ParseConfig config;
        if(argc != 2)
        {

            std::cout << "Accepting only one file config"<<std::endl;
            return(1);
        } 
            
            
         std::string	file = argv[1];
        config.splitConfigElements(file);
        std::cout<< "All good" <<std::endl;
        int nums = 3;
        std::map<std::string, std::vector<configServer>> servers = config.server_getter();/////FOR NOW, PORT coming from config file
         std::cout<< "2" <<std::endl;
        std::vector<configServer> server_list = servers[0];
         std::cout<< "3" <<std::endl;
        configServer server1 = server_list[0];
         std::cout<< "4" <<std::endl;
        std::string port_string = server1.port;
         std::cout<< "5" <<std::endl;
        int port = stoi(port_string);
         std::cout<< "6" <<std::endl;
        WebServ webserv(AF_INET, SOCK_STREAM,0 , port, INADDR_ANY, 32);
        // (domain, type, protocol 0 => by default for SOCK_STREAM => TCP)
        
        webserv.launch(nums);

    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}