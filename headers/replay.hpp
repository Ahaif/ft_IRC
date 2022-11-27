#ifndef REPLAY_HPP
#define REPLAY_HPP

#define CLIENT_INFORMATION _clientMap[fd]->get_Nickname() + "!" + _clientMap[fd]->get_Username() + "@" + _clientMap[fd]->get_Host()
#define ERR_NEEDMOREPARAMS ":Not enough parameters"
#define ERR_ALREADYREGISTERED  ":You may not reregister"
#define ERR_PASSWDMISMATCH ":Password incorrect"
#define ERR_NONICKNAMEGIVEN ":No nickname given"
#define ERR_NICKNAMEINUSE ":Nickname is already in use"
#define ERR_ERRONEUSNICKNAME  ":Erroneus nickname"
#define RPL_WELCOME " :Welcome to the " + _name + " Network, " + CLIENT_INFORMATION
#define ERR_NOTREGISTERED ":You have not registered"
#define ERR_NOSUCHCHANNEL ":No such channel"
#define ERR_BADCHANNELKEY ":Cannot join channel (+k)"
#define ERR_NOTONCHANNEL  ":You're not on that channel"
#define RPL_NOTOPIC  ":No topic is set"
#define ERR_INVITEONLYCHAN  ":Cannot join channel (+i)"
#define ERR_CHANOPRIVSNEEDED  ":You're not channel operator"
#define ERR_NOSUCHNICK  ":No such nick/channel"
#define ERR_KEYSET  ":Channel key already set"
#define ERR_UNKNOWNMODE ":is unknown mode char to me"
#define ERR_USERONCHANNEL ":is already on channel"
#define RPL_ENDOFNAMES ":End of /NAMES list"
#define RPL_LISTSTART "Channel :Users  Name"
#define RPL_LISTEND ":End of /LIST"
#define ERR_UNKNOWNCOMMAND ":Unknown command"


#endif