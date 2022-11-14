#include "../headers/server.hpp"

std::string		server:: _kick_fromChnl(std::string ChannelName, std::string message, std::vector<std::string> users, int fd)
{
	
	std::map<std::string, Channel *>::iterator it = this->_channels.find(ChannelName);
	int ret = 0;
	if (it != this->_channels.end())
	{
		std::pair<client *, int> user = it->second->pick_user_role(fd);
		if (user.second == 1)
		{
			std::vector<std::string>::iterator userit = users.begin();
			
			while (userit != users.end())
			{
				ret = _find_FdBy_NickName(*userit);
				if (ret == -1)
					return (_printMessage("441", this->_clientMap[ret]->get_Nickname(), ChannelName.append(" :They aren't on that channel")));
				std::string reply = "KICK " + ChannelName;
				if (message.empty())
					reply.append("\n");
				else
					reply.append(" " + message + "\n");
				_channels[ChannelName]->removeMember(_clientMap[ret]);
				// if(_channels[ChannelName]->memberSize() == 0)
				// 	_channels.erase(ChannelName);
				//NOTIFY USERS ABOUT REPLY
				// std :: cout << "user: " << _clientMap[ret]->get_Nickname() << "removed from "<< _channels[ChannelName]->get_name() << std :: endl;
				userit++;
			}
		}
		else if (user.second == -1  /* Not in channel */)
			return (_printMessage("442", this->_clientMap[ret]->get_Nickname(), ChannelName.append(" :You're not on that channel")));
		else
			return (_printMessage("482", this->_clientMap[ret]->get_Nickname(), ChannelName.append(" :You're not channel operator")));
		return ("");
	}
	return (_printMessage("403", this->_clientMap[ret]->get_Nickname(), ChannelName.append(" :No such channel")));
}

std:: string server :: kick_user(request request, int fdClient)
{

    if (!this->_clientMap[fdClient]->get_registration())
		return ( "You have not registered");
	std :: cout << "PASSEd---01\n";
	if (request.args.size() < 2)
        return (_printMessage("461", "KICK",  ERR_NEEDMOREPARAMS));
	std::vector<std::string> channels(comma_sep(request.args[0]));
	std::vector<std::string> users(comma_sep(request.args[1]));
	std :: cout << "PASSEd---02\n";
	std::vector<std::string>::iterator it = channels.begin();
	while (it != channels.end())
	{
		std::string ret;
		if (request.args.size() == 3)
			ret = _kick_fromChnl(*it, request.args[2], users, fdClient);
		else
			ret = _kick_fromChnl(*it, "Default msg", users, fdClient);
	
		if(!ret.empty())
			return(ret);
		it++;
	}
	return ("");
}
