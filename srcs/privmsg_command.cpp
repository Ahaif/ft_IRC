#include "../headers/server.hpp"



int server :: sendMsg(int fd, std :: string msg)
{
    int total = 0;
	int bytesleft = msg.length();
	int b;

	while (total < (int)msg.length())
	{
		b = send(fd, msg.c_str() + total, bytesleft, 0);
		if (b == -1) break;
		total += b;
		bytesleft -= b;
	}
	return (b == -1 ? -1 : 0);
}




std :: string server :: prvmsg_user(request req, int fd)
{
    int userFd = _find_FdBy_NickName(req.args[0]);
    if (userFd == -1)
       return (format_msg("401", this->_clientMap[fd]->get_Nickname(), " :No such nick/channel"));
    std::string ans = this->_clientMap[fd]->getUserPerfix();
	ans.append(req.cmd + " " + req.args[0] + " :" + req.args[1] + "\n");
	if (sendMsg(userFd, ans) == -1)
				std::cout << "_sendall() error: " << strerror(errno) << std::endl;
	return ("");

}

std :: string server :: send_to_allUsers(Channel *chnlName, int senderFd, std :: string msg, bool includeSender)
{
    std::map<int, client *> allusers = chnlName->collect_users();
	std::map<int, client *>::iterator it = allusers.begin();
	std::string reply = this->_clientMap[senderFd]->getUserPerfix();
	reply.append(msg);
	while (it != allusers.end())
	{
		if (includeSender == true)
		{
			if (sendMsg(it->first, reply) == -1)
			{
				std::cout << "_sendall() error: " << strerror(errno) << std::endl;
				return ("");
			}
		}
		else if (senderFd != it->first)
		{
			if (sendMsg(it->first, reply) == -1)
			{
				std::cout << "_sendall() error: " << strerror(errno) << std::endl;
				return ("");
			}
		}
		it++;
	}
	return ("");
}


std :: string server :: prvmsg_chnl(request req, int fd)
{
    std::map<std::string, Channel *>::iterator it = this->_channels.find(req.args[0]);
	if (it != this->_channels.end())
	{
		std::pair<client *, int> user = it->second->pick_user_role(fd);
		if (user.second == -1 )
			return (format_msg("404", this->_clientMap[fd]->get_Nickname(), req.args[0].append(" :Cannot send to channel")));
		std::string msg("PRIVMSG " + req.args[0] + " :" + req.args[1] + "\n");
		// _sendToAllUsers(it->second, i, msg);
        send_to_allUsers(it->second, fd, msg, false);
	}
	else
		return (format_msg("401", this->_clientMap[fd]->get_Nickname(), req.args[0].append(" :No such nick/channel")));
	return ("");

}

std :: string server :: prvmsg(request req, int fd)
{
    if(!this->_clientMap[fd]->get_registration())
        return(format_msg("401", this->_clientMap[fd]->get_Nickname(), ":No such nick/channel"));
    if (req.args.size() < 2)
		return (format_msg("461", this->_clientMap[fd]->get_Nickname(), ":Not enough parameters"));
    if(req.args.size() == 2)
    {
        if (req.args[0].find(",") != std::string::npos)
            return("ERR_TOOMANYTARGETS");
        else
        {
            if (req.args[0][0] != '+' && req.args[0][0] != '&' && req.args[0][0] != '#' && req.args[0][0] != '!')
                return(prvmsg_user(req, fd));
            else
                return(prvmsg_chnl(req, fd));

        }

    }
    return("");
}



// 404    "<client> <channel> :Cannot send to channel"
// 407
// 411
// 412
// 413
// 414
// 301
