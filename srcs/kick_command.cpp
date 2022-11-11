#include "../headers/server.hpp"

std::string		server:: kick_from_chnl(std::string ChannelName, std::string message, std::vector<std::string> users, int fd)
{
	std::map<std::string, Channel *>::iterator it = this->_channels.find(ChannelName);
	if (it != this->_channels.end())
	{
		std::pair<client *, int> user = it->second->pick_user_role(fd);
		if (user.second == 1)
		{
			std::vector<std::string>::iterator user = users.begin();
			int ret = 0;
			while (user != users.end())
			{
				ret = _find_FdBy_NickName(*user);
				if (ret == -1)
					return ( "is not on that channel");
				std::string reply = "KICK " + ChannelName;
				if (message.empty())
					reply.append("\n");
				else
					reply.append(" " + message + "\n");
				user++;
			}
		}
		else if (user.second == -1  /* Not in channel */)
			return ( " :You're not on that channel");
		else
			return (" :You're not channel operator");
		return ("");
	}
	return (" :No such channel");
}

std:: string server :: kick_user(request request, int fdClient)
{


    std :: cout << "Kick cmd enter\n";
    if (!this->_clientMap[fdClient]->get_registration())
		return ( "You have not registered");
	if (request.args.size() < 2)
        return("ERROR_PARAM_SIZE");
	std::vector<std::string> channels(comma_sep(request.args[0]));
	std::vector<std::string> users(comma_sep(request.args[1]));
	std::vector<std::string>::iterator it = channels.begin();
	while (it != channels.end())
	{
		std::string ret;
		if (request.args.size() == 3)
            std ::cout << "req args size is: " << request.args.size() << std :: endl;
			// ret = _kickedFromChannel(*it, request.args[2], users, i);
		else
            std ::  cout << "req args size is: " << request.args.size() << std :: endl;
			// ret = _kickedFromChannel(*it, "", users, i);
		if (!ret.empty())
			return(ret);
		it++;
	}
	return ("");
}