#include "WebServ.hpp"

int main(int argc, char **argv)
{ 
    (void)argv;
    (void) argc;
    try{
        // if(argc != 2)
        //     std::cout << "Accepting only one file config"<<std::endl;
        WebServ webserv(AF_INET, SOCK_STREAM,0 , 8084, INADDR_ANY, 32);
        
        webserv.launch();

    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}