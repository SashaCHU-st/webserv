#include "Webserv.hpp"
int main(int argc, char **argv)
{
    (void)argv;
    try{
        if(argc != 2)
            std::cout << "Acceptiong only one file config"<<std::endl;

    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}