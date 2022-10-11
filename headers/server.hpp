
#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <cstring>
#include <algorithm>
#include <utility>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>
#include <time.h>


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
        ~server();
        void    start_server();
    private : 
        void    create_socket(std :: string port);
        void    new_connection();
        void    add_to_poll(int fd);

};



#endif