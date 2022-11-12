#include "../headers/server.hpp"


std::vector<std::string> server::comma_sep(std :: string chnlist)
{
    std::vector<std::string> ret;
	size_t pos = 0;
	while ((pos = chnlist.find(",")) != std::string::npos)
	{
		ret.push_back(chnlist.substr(0, pos));
		chnlist.erase(0, pos + 1);
	}
	ret.push_back(chnlist.substr(0, pos));
	return (ret);
}


std::string server::part_command(request req, int fd)
{
    std::vector<std::string> names;
    std::vector<std::string> reasons;
    if (!this->_clientMap[fd]->get_registration())
        send_replay(_clientMap[fd], "451", ERR_NOTREGISTERED);
    else if (req.args.size() == 0)
        send_replay(_clientMap[fd], "461", ERR_NEEDMOREPARAMS);
    else
    {
        names = split(req.args[0], ",");
        if (req.args.size() > 1)
            reasons = split(req.args[1], ",");
        if (names.size() > reasons.size())
            reasons.resize(names.size(), "");
        for (size_t i = 0; i < names.size(); i++)
        {
            if (_channels.find(names[i]) != _channels.end())
            {
                if (_channels[names[i]]->isMember(_clientMap[fd]))
                {
                    _channels[names[i]]->removeMember(_clientMap[fd]);
                    std::cout << _channels[names[i]]->get_onlineUsers() << std::endl;
                    if (_channels[names[i]]->get_onlineUsers() == 0)
                    {
                        _channels.erase(names[i]);
                        send_replay(_clientMap[fd], "Channel: " + names[i], " is removed\n");
                    }
                    send_replay(_clientMap[fd], " leave channel ", names[i] + "\n");
                }
                else
                    send_replay(_clientMap[fd], "442", names[i] + ERR_NOTONCHANNEL);
            }
            else
                send_replay(_clientMap[fd], "403", names[i] + ERR_NOSUCHCHANNEL);
        }
    }
    return "";
}