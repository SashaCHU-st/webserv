// #include "WebServ.hpp"
// #include <csignal>

// void signalHandler(int signal) {
//     std::cerr << "Caught signal: " << signal << std::endl;
//     exit(signal);
// }

// int main(int argc, char **argv)
// { 
//     signal(SIGSEGV, signalHandler); // Seg
//     signal(SIGINT, signalHandler); // Ctrl+C
//     signal(SIGTERM, signalHandler); // Termin
//     (void)argv;
//     (void) argc;
//     try{
//         // if(argc != 2)
//         //     std::cout << "Accepting only one file config"<<std::endl;
//         int nums = 3;
//         WebServ webserv(AF_INET, SOCK_STREAM,0 , 2999, INADDR_ANY, 32);
        
//         webserv.launch(nums);

//     }
//     catch(std::exception& e)
//     {
//         std::cout << e.what() << std::endl;
//         return 1;
//     }
//     return 0;
// }