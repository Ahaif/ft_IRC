#include "../headers/server.hpp"




server :: server(std :: string name, int max_online, std :: string port, std:: string password)
{
    this->_max_online = max_online;
    this->_name = name;
    this->_password = password;
    create_socket(port);


}

void server :: start_server()
{
    while(42)
    {
        
    }
}