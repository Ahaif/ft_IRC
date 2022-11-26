#include "../headers/server.hpp"

std::string server::list_command(request req, int fd)
{
	client *clnt = _clientMap[fd];
	std::string prefix = ":" + _name + " ";
	std::string nick = clnt->get_Nickname();
	std::string message = "";
	std::string topic = "";

	if (clnt->get_registration() == false)
		send_replay1(clnt, prefix, "451", nick, ERR_NOTREGISTERED);
	else if (req.args.size() != 0 && req.args[0] != "")
	{
		std::vector<std::string> names = split(req.args[0], ",");
		send_replay1(clnt, prefix, "321", nick, RPL_LISTSTART);
		for (size_t i = 0; i < names.size(); i++)
		{
			std::map<std::string, Channel *>::iterator it = _channels.find(names[i]);
			if (it != _channels.end() && (it->second->isSecret() == false || it->second->isMember(clnt) == true))
			{
				message = it->first + " " + std::to_string(it->second->memberSize()) + " :";
				if (it->second->isPrivate() == true && it->second->isMember(clnt) == false)
					topic = "";
				else
					topic = it->second->get_topic();
				message += topic;
				send_replay1(clnt, prefix, "322", nick, message);
			}
		}
		send_replay1(clnt, prefix, "322", nick, RPL_LISTEND);
	}
	else
	{
		std::map<std::string, Channel *>::iterator it = _channels.begin();
		send_replay1(clnt, prefix, "321", nick, RPL_LISTSTART);
		for (; it != _channels.end(); it++)
		{
			if (it->second->isSecret() == false || it->second->isMember(clnt) == true)
			{
				message = it->first + " " + std::to_string(it->second->memberSize()) + " :";
				if (it->second->isPrivate() == true && it->second->isMember(clnt) == false)
					topic = "";
				else
					topic = it->second->get_topic();
				message += topic;
				send_replay1(clnt, prefix, "322", nick, message);
			}
		}
		send_replay1(clnt, prefix, "322", nick, RPL_LISTEND);
	}
	return "";
}