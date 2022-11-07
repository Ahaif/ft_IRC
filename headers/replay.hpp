#ifndef REPLAY_HPP
#define REPLAY_HPP

#define CLIENT_INFORMATION _clientMap[fd]->get_Nickname() + "!" + _clientMap[fd]->get_Username() + "@" + _clientMap[fd]->get_Host() + "\n"
#define ERR_NEEDMOREPARAMS req.cmd + " : Not enough parameters\n"
#define ERR_ALREADYREGISTERED req.cmd + " :You may not reregister\n"
#define ERR_PASSWDMISMATCH req.cmd + " :Password incorrect\n"
#define ERR_NONICKNAMEGIVEN req.cmd + " :No nickname given\n"
#define ERR_NICKNAMEINUSE req.args[0] + " :Nickname is already in use\n"
#define ERR_ERRONEUSNICKNAME req.args[0] + " :Erroneus nickname\n"
#define RPL_WELCOME " :Welcome to the " + _name + " Network, " + CLIENT_INFORMATION
#define ERR_NOTREGISTERED ":You have not registered\n"
#define ERR_NOSUCHCHANNEL names[i] + " No such channel\n"
#define ERR_BADCHANNELKEY names[i] + " :Cannot join channel (+k)\n"


#endif