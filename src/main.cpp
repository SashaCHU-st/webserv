// #include "Webserv.hpp"
// int main(int argc, char **argv)
// { 
//     (void)argv;
//     try{
//         if(argc != 2)
//             std::cout << "Accepting only one file config"<<std::endl;

//     }
//     catch(std::exception& e)
//     {
//         std::cout << e.what() << std::endl;
//         return 1;
//     }
//     return 0;
// }

#include "Launching.hpp"

// int main()
// {
// }


// #include "Webserv.hpp"
int main(int argc, char **argv)
{ 
    (void)argv;
    (void) argc;
    try{
        // if(argc != 2)
        //     std::cout << "Accepting only one file config"<<std::endl;
    Launching webserv;

    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}