#include "headers/server.hpp"

int main(int ac, char **av)
{
    if (ac == 3)
    {
        server srv("abdel_test", 10, av[1], av[2]);
        std :: cout << "Server Starting ..." << std :: endl;
        srv.start_server();
    }
    else
        std :: cout << "Error ARG , add Port Number and password" << std :: endl;
}