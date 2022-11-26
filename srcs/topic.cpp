#include "../headers/server.hpp"

std::string server::topic_command(request req, int fd)
{
	client *clnt = _clientMap[fd];
	std::string prefix = ":" + _name + " ";
	std::string nick = clnt->get_Nickname();

	if (clnt->get_registration() == false)
		send_replay1(clnt, prefix, "451", nick, ERR_NOTREGISTERED);
	else if (req.args.size() == 0 || (req.args.size() == 1 && req.args[0] == ""))
		send_replay1(clnt, prefix, "461", nick, req.cmd + " " + ERR_NEEDMOREPARAMS);
	else
	{
		if (_channels.find(req.args[0]) != _channels.end())
		{
			if (_channels[req.args[0]]->isMember(clnt))
			{
				if (req.args.size() == 1)
				{
					if ((_channels[req.args[0]]->get_topic()).empty())
						send_replay1(clnt, prefix, "331", nick, req.args[0] + " " + RPL_NOTOPIC);
					else
						send_replay1(clnt, prefix, "332", nick, req.args[0] + " :" + _channels[req.args[0]]->get_topic() + "\n");
				}
				else if (_channels[req.args[0]]->isTopicSet() == true && _channels[req.args[0]]->isOperator(clnt) == false)
					send_replay1(clnt, prefix, "482", nick, req.args[0] + " " + ERR_CHANOPRIVSNEEDED);
				else
				{
					prefix = clnt->getUserPerfix();
					_channels[req.args[0]]->set_topic(req.args[1]);
					send_replay1(clnt, prefix, "TOPIC", req.args[0], ":" + _channels[req.args[0]]->get_topic() + "\n");
				}
			}
			else
				send_replay1(clnt, prefix, "442", nick, req.args[0] + " " + ERR_NOTONCHANNEL);
		}
		else
			send_replay1(clnt, prefix, "403", nick, req.args[0] + " " + ERR_NOSUCHCHANNEL);
	}
	return "";
}