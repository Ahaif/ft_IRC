#include "../headers/server.hpp"

std::string server::notice_command(request req, int fd)
{
	client *clnt = _clientMap[fd];
	if (this->_clientMap[fd]->get_registration() && req.args.size() == 2)
	{
		if (req.args[0][0] == '#')
		{
			std::map<std::string, Channel *>::iterator it = _channels.find(req.args[0]);
			if (it != _channels.end())
			{
				std::map<int, client *>::iterator it2 = it->second->getMembers().begin();
				for (; it2 != it->second->getMembers().end(); it2++)
				{
					send_replay1(it2->second, clnt->getUserPerfix(), req.cmd, req.args[0], ":" + req.args[1]);
				}
			}
		}
		else
		{
			std::map<int, client *>::iterator it = _clientMap.begin();
			for (; it != _clientMap.end(); it++)
			{
				if (it->second->get_Nickname() == req.args[0])
				{
					send_replay1(it->second, clnt->getUserPerfix(), req.cmd, req.args[0], ":" + req.args[1]);
					break;
				}
			}
		}
	}
	return "";
}