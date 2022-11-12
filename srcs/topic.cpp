#include "../headers/server.hpp"

std::string server::topic_command(request req, int fd)
{
	if (!this->_clientMap[fd]->get_registration())
		send_replay(_clientMap[fd], "451", ERR_NOTREGISTERED);
	else if (req.args.size() == 0)
		send_replay(_clientMap[fd], "461", ERR_NEEDMOREPARAMS);
	else
	{
		if (_channels.find(req.args[0]) != _channels.end())
		{
			if (_channels[req.args[0]]->isMember(_clientMap[fd]))
			{
				if (req.args.size() == 1)
				{
					if ((_channels[req.args[0]]->get_topic()).empty())
						send_replay(_clientMap[fd], "331", req.args[0] + RPL_NOTOPIC);
					else
						send_replay(_clientMap[fd], "332", req.args[0] + " :" + _channels[req.args[0]]->get_topic() + "\n");
				}
				else
				{
					_channels[req.args[0]]->set_topic(req.args[1]);
					send_replay(_clientMap[fd], "TOPIC", ":" + _channels[req.args[0]]->get_topic() + "\n");
				}
			}
			else
				send_replay(_clientMap[fd], "442", req.args[0] + ERR_NOTONCHANNEL);
		}
		else
			send_replay(_clientMap[fd], "403", req.args[0] + ERR_NOSUCHCHANNEL);
	}
	return "";
}