
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

#include "request.hpp"
#include "client.hpp"

class request;
class client;

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
        std :: map<int, client*> _clientMap;

    public:
        server(std :: string name, int max_online, std :: string port, std :: string password);
        ~server();
        void    start_server();
    private : 
        void            create_socket(std :: string port);
        void            new_connection();
        void            add_to_poll(int fd);
        void            remove_from_poll(int fd);
        void            handle_request(int i);
        std :: string   parse_request(std :: string req, int i);
        request         split_msg(std :: string req);
        std :: string   set_pssw(request req, int fd);

};



#endif