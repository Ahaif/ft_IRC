#include "../headers/server.hpp"

std::string server::invite_command(request req, int fd)
{
	client *clnt = _clientMap[fd];
	std::string prefix = ":" + _name + " ";
	std::string nick = clnt->get_Nickname();
	client *invited;

	if (clnt->get_registration() == false)
		send_replay(clnt, prefix, "451", nick, ERR_NOTREGISTERED);
	else if (req.args.size() < 2 || (req.args.size() == 2 && req.args[1] == ""))
		send_replay(clnt, prefix, "461", nick, req.cmd + " " + ERR_NEEDMOREPARAMS);
	else if (_channels.find(req.args[1]) != _channels.end())
	{
		if (_channels[req.args[1]]->isMember(clnt))
		{
			if (_channels[req.args[1]]->isOperator(clnt))
			{
				std::map<int, client *>::iterator it = _clientMap.begin();
				for (; it != _clientMap.end(); it++)
				{
					if (it->second->get_Nickname() == req.args[0])
					{
						invited = it->second;
						break;
					}
				}
				if (it != _clientMap.end())
				{
					if (_channels[req.args[1]]->isMember(invited) == true)
						send_replay(clnt, prefix, "443", nick, req.args[0] + " " ERR_USERONCHANNEL);
					else
					{
						prefix = clnt->getUserPerfix();
						if (_channels[req.args[1]]->isInviteOnly() == true)
						{
							invited->add_invited_channel(req.args[1], _channels[req.args[1]]);
							_channels[req.args[1]]->add_invited_client(invited);
						}
						send_replay(invited, prefix, "INVITE", req.args[0], req.args[1]);
						send_replay(clnt, prefix, "341", nick, req.args[1] + " " + req.args[0]);
					}
				}
				else
					send_replay(clnt, prefix, "401", nick, req.args[0] + " " + ERR_NOSUCHNICK);
			}
			else
				send_replay(clnt, prefix, "482", nick, req.args[1] + " " + ERR_CHANOPRIVSNEEDED);
		}
		else
			send_replay(clnt, prefix, "442", nick, req.args[1] + " " + ERR_NOTONCHANNEL);
	}
	else
		send_replay(clnt, prefix, "401", nick, req.args[1] + " " + ERR_NOSUCHNICK);
	return "";
}