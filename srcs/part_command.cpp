#include "../headers/server.hpp"

std::vector<std::string> server::comma_sep(std ::string chnlist)
{
    std::vector<std::string> ret;
    size_t pos = 0;
    pos = chnlist.find(",");
    if((pos = chnlist.find(",")) == std::string::npos)
    {
        ret.push_back(chnlist);
        return(ret);
    }
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
    client *clnt = _clientMap[fd];
    std::string prefix = ":" + _name + " ";
    std::string nick = clnt->get_Nickname();
    std::string message;

    if (clnt->get_registration() == false)
        send_replay1(clnt, prefix, "451", nick, ERR_NOTREGISTERED);
    else if (req.args.size() == 0 || (req.args.size() == 1 && req.args[0] == ""))
        send_replay1(clnt, prefix, "461", nick, req.cmd + " " + ERR_NEEDMOREPARAMS);
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
                if (_channels[names[i]]->isMember(clnt))
                {
                    message = "PART " + names[i] + " :" + reasons[i] + "\n";
                    send_to_allUsers(_channels[names[i]], fd, message, true);
                    _channels[names[i]]->remove_from_channel(clnt);
                    clnt->part_from_channel(_channels[names[i]]);
                    if (_channels[names[i]]->get_onlineUsers() == 0)
                        _channels.erase(names[i]);
                }
                else
                    send_replay1(clnt, prefix, "442", nick, names[i] + " " + ERR_NOTONCHANNEL);
            }
            else
                send_replay1(clnt, prefix, "403", nick, names[i] + " " + ERR_NOSUCHCHANNEL);
        }
    }
    return "";
}