
#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <netdb.h>
#include<string.h>
#include <unistd.h>
#include <struct.h>
#include <poll.h>



class server
{
    private:
        int             _socketFd;
        int             _addrLen;
        int             _max_online;
        struct pollfd	*_pfds;
        int             _online_client;
        std::string     _name;
        std :: string   _password;

    public:
        server(std :: string name, int max_online, std :: string port, std :: string password);
        void    start_server();
    private : 
        void    create_socket(std :: string port);


};



#endif