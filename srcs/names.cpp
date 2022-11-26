#include "../headers/server.hpp"

std::string server::names_command(request req, int fd)
{
	client *clnt = _clientMap[fd];
	std::string prefix = ":" + _name + " ";
	std::string nick = clnt->get_Nickname();
	std::string message = "";
	std::string nickNames = "";
	std::set<std::string> nickSet;

	if (clnt->get_registration() == false)
		send_replay1(clnt, prefix, "451", nick, ERR_NOTREGISTERED);
	else if (req.args.size() != 0 && req.args[0] != "")
	{
		std::vector<std::string> names = split(req.args[0], ",");
		for (size_t i = 0; i < names.size(); i++)
		{
			std::map<std::string, Channel *>::iterator it = _channels.find(names[i]);
			if (it != _channels.end() && it->second->isPrivate() == false && it->second->isSecret() == false)
			{
				message = "= " + it->first + " :";
				message += it->second->getMembersNickNames();
				send_replay1(clnt, prefix, "353", nick, message);
			}
			send_replay1(clnt, prefix, "366", nick, names[i] + " " + RPL_ENDOFNAMES);
		}
	}
	else
	{
		std::map<std::string, Channel *>::iterator it = _channels.begin();
		for (; it != _channels.end(); it++)
		{
			if (it->second->isPrivate() == false && it->second->isSecret() == false)
			{
				message = "= " + it->first + " :";
				message += it->second->getMembersNickNames();
				send_replay1(clnt, prefix, "353", nick, message);
				send_replay1(clnt, prefix, "366", nick, it->first + " " + RPL_ENDOFNAMES);
			}
			else
			{
				std::map<int, client *>::iterator it2 = it->second->getMembers().begin();
				for (; it2 != it->second->getMembers().end(); it2++)
				{
					nickSet.insert(it2->second->get_Nickname());
				}
			}
		}
		std::map<int, client *>::iterator it2 = _clientMap.begin();
		for (; it2 != _clientMap.end(); it2++)
		{
			if (it2->second->isHasNoChannel() == true)
			{
				nickSet.insert(it2->second->get_Nickname());
			}
		}
		if (nickSet.size() != 0)
		{
			std::set<std::string>::iterator it3 = nickSet.begin();
			for (; it3 != nickSet.end(); it3++)
			{
				nickNames += *it3 + " ";
			}
			message = "= * :";
			message += nickNames;
			send_replay1(clnt, prefix, "353", nick, message);
		}
		send_replay1(clnt, prefix, "366", nick, std::string("* ") + RPL_ENDOFNAMES);
	}
	return "";
}
