#ifndef REPLAY_HPP
#define REPLAY_HPP

#define CLIENT_INFORMATION _clientMap[fd]->get_Nickname() + "!" + _clientMap[fd]->get_Username() + "@" + _clientMap[fd]->get_Host() + "\n"
#define ERR_NEEDMOREPARAMS " : Not enough parameters"
#define ERR_ALREADYREGISTERED  " :You may not reregister"
#define ERR_PASSWDMISMATCH " :Password incorrect"
#define ERR_NONICKNAMEGIVEN " :No nickname given"
#define ERR_NICKNAMEINUSE " :Nickname is already in use"
#define ERR_ERRONEUSNICKNAME  " :Erroneus nickname"
#define RPL_WELCOME " :Welcome to the " + _name + " Network, " + CLIENT_INFORMATION
#define ERR_NOTREGISTERED ":You have not registered"
#define ERR_NOSUCHCHANNEL " No such channel"
#define ERR_BADCHANNELKEY names[i] + " :Cannot join channel (+k)\n"
#define ERR_NOTONCHANNEL  " :You're not on that channel\n"
#define RPL_NOTOPIC  " :No topic is set\n"


#endif