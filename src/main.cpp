#include "WebServ.hpp"
#include "Signal.hpp"

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
        // if(argc != 2)
        //     std::cout << "Accepting only one file config"<<std::endl;
        int nums = 3;
        int port = 4050;/////FOR NOW, PORT coming from config file
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