
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
#include "replay.hpp"
#include "channel.hpp"

class request;
class client;
class Channel;

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
        std :: vector<std :: string> _clientName;
        std::map<std::string , Channel *> _channels;
    public:
        server(std :: string name, int max_online, std :: string port, std :: string password);
        ~server();
        void    start_server();
    private : 
        void            create_socket(std :: string port);
        void            new_connection();
        void            add_to_poll(int fd);
        void            remove_from_poll(int fd);
        void            handle_request(int i , client *client);
        std :: string   parse_request(std :: string req, int i);
        request         split_msg(std :: string req);
        std :: string   set_pssw(request req, int fd);
        std :: string   registerName(request req, int fd);
        std :: string   set_userName(request req, int fd);
        std :: string   set_Oper(request req, int fd);
        std :: string   set_user_mode(request req, int fd);
        std :: string   join_chnl(request req, int fd);
        void send_replay(client *client, std::string replayNb, std::string message);
        std::vector<std::string> split(std::string str, std::string sep);



        std::string                 _partCmd( request request, int i);
        std :: string               kick_user(request request, int i);
        std::vector<std::string>    comma_sep(std :: string chnlist);
        std::string                 kick_from_chnl(std::string ChannelName, std::string message, std::vector<std::string> users, int i);
        int	                        _find_FdBy_NickName(std::string NickName);
};



#endif