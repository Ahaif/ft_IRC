#include "../headers/server.hpp"

std::string server::set_channel_mode(request req, int fd)
{
	std::map<std::string, Channel *>::iterator it = _channels.find(req.args[0]);
	client *clnt = _clientMap[fd];
	std::string prefix = ":" + _name + " ";
	std::string nick = clnt->get_Nickname();
	bool status = true;
	char mode;
	std::string message;
	if (it != _channels.end())
	{
		if (it->second->isMember(_clientMap[fd]) == true || req.args.size() == 1)
		{
			if (it->second->isOperator(_clientMap[fd]) == true || req.args.size() == 1)
			{
				if (req.args.size() == 1)
					send_replay1(clnt, prefix, "324", nick, req.args[0] + " +" + it->second->get_modes());
				else
				{
					for (size_t i = 0; i < req.args[1].size(); i++)
					{
						mode = req.args[1][i];
						message = "MODE " + it->first;
						if (i == 0 && (mode == '-' || mode == '+'))
						{
							if (mode == '-')
								status = false;
						}
						else if (mode == 'i' || mode == 'm' || mode == 'p' || mode == 's' || mode == 't' || mode == 'n')
						{
							it->second->set_mode(req.args[1][i], status, "");
							if (status == true)
								send_to_allUsers(it->second, fd, message + " +" + req.args[1][i] + "\n", true);
							else
								send_to_allUsers(it->second, fd, message + " -" + req.args[1][i] + "\n", true);
						}
						else if (mode == 'k' || mode == 'l')
						{
							if (status == true && req.args.size() < 3)
								send_replay1(clnt, prefix, "461", nick, req.cmd + " " + ERR_NEEDMOREPARAMS);
							else if (mode == 'k' && it->second->isKeySet() == true)
								send_replay1(clnt, prefix, "467", nick, req.args[0] + " " + ERR_KEYSET);
							else if (status == true)
							{
								it->second->set_mode(req.args[1][i], status, req.args[2]);
								send_to_allUsers(it->second, fd, message + " +" + req.args[1][i] + " " + req.args[2] + "\n", true);
							}
							else
							{
								it->second->set_mode(req.args[1][i], status, "");
								send_to_allUsers(it->second, fd, message + " -" + req.args[1][i] + "\n", true);
							}
						}
						else
							send_replay1(clnt, prefix, "472", nick, std::string(1, req.args[1][i]) + " " + ERR_UNKNOWNMODE);
					}
				}
			}
			else
				send_replay1(clnt, prefix, "482", nick, req.args[0] + " " + ERR_CHANOPRIVSNEEDED);
		}
		else
			send_replay1(clnt, prefix, "442", nick, req.args[0] + " " + ERR_NOTONCHANNEL);
		return ("");
	}
	send_replay1(clnt, prefix, "401", nick, req.args[0] + " " + ERR_NOSUCHNICK);
	return ("");
}

std::string server::mode_command(request req, int fd)
{
	client *clnt = _clientMap[fd];
	std::string prefix = ":" + _name + " ";
	std::string nick = clnt->get_Nickname();

	if (clnt->get_registration() == false)
		send_replay1(clnt, prefix, "451", clnt->get_Nickname(), ERR_NOTREGISTERED);
	else if (req.args.size() == 0 || (req.args.size() == 1 && req.args[0] == ""))
		send_replay1(clnt, prefix, "461", nick, req.cmd + " " + ERR_NEEDMOREPARAMS);
	else
	{
		if (req.args[0] == _clientMap[fd]->get_Nickname())
			return set_user_mode(req, fd);
		else
		{
			if (req.args[0][0] == '#')
				set_channel_mode(req, fd);
			else
				send_replay1(clnt, prefix, "401", nick, req.args[0] + " " + ERR_NOSUCHNICK);
		}
	}
	return ("");
}