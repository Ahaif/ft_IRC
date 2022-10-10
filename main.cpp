#include <iostream>

#include "headers/server.hpp"







int main(int ac, char **av)
{
    if (ac == 3)
    {
        server srv("abdel_test", 10, av[1], av[2]);
        
        srv.start_server();
        std :: cout << "Server Starting \n";
    }
    else
    {
        std :: cout << "Error ARG , add Port Number and password" << std :: endl;
    }
}