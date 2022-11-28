#include "../headers/server.hpp"

std ::string server ::join_chnl(request req, int fd)
{
    std::vector<std::string> names;
    std::vector<std::string> keys;
    client *clnt = _clientMap[fd];
    std::string prefix = ":" + _name + " ";
    std::string nick = clnt->get_Nickname();

    if (clnt->get_registration() == false)
        send_replay(clnt, prefix, "451", nick, ERR_NOTREGISTERED);
    else if (req.args.size() == 0 || (req.args.size() == 1 && req.args[0] == ""))
        send_replay(clnt, prefix, "461", nick, req.cmd + " " + ERR_NEEDMOREPARAMS);
    else
    {
        names = split(req.args[0], ",");
        if (req.args.size() > 1)
            keys = split(req.args[1], ",");
        if (names.size() > keys.size())
            keys.resize(names.size(), "");
        for (size_t i = 0; i < names.size(); i++)
        {
            if (_channels.find(names[i]) == _channels.end())
            {
                if (names[i][0] != '#')
                    send_replay(clnt, prefix, "403", nick, names[i] + " " + ERR_NOSUCHCHANNEL);
                else
                {
                    _channels[names[i]] = new Channel(names[i], keys[i], _clientMap[fd]);
                    _channels[names[i]]->addMember(_clientMap[fd], 1, 1);
                    _clientMap[fd]->add_channel(names[i], _channels[names[i]]);
                    _clientMap[fd]->set_operator();
                    send_to_allUsers(_channels[names[i]], fd, "JOIN :" + names[i] + "\n", true);
                    request newreq(split_msg("NAMES " + names[i]));
                    names_command(newreq, fd);
                }
            }
            else if (_channels[names[i]]->isInviteOnly() == true && clnt->is_invited_to(_channels[names[i]]) == false)
                send_replay(clnt, prefix, "473", nick, names[i] + " " + ERR_INVITEONLYCHAN);
            else if (_channels[names[i]]->isLimitSet() == true && (_channels[names[i]]->get_onlineUsers() >= _channels[names[i]]->get_limitUsers()))
                send_replay(clnt, prefix, "471", nick, names[i] + " " + ERR_CHANNELISFULL);
            else if (_channels[names[i]]->get_key() == keys[i])
            {
                if (_channels[names[i]]->isInviteOnly() == true)
                {
                    clnt->part_from_channel(_channels[names[i]]);
                    _channels[names[i]]->remove_from_channel(clnt);
                }
                _channels[names[i]]->addMember(_clientMap[fd], 0, 0);
                _clientMap[fd]->add_channel(names[i], _channels[names[i]]);
                send_to_allUsers(_channels[names[i]], fd, "JOIN :" + names[i] + "\n", true);
                request newreq(split_msg("NAMES " + names[i]));
                names_command(newreq, fd);
            }
            else
                send_replay(clnt, prefix, "475", nick, names[i] + " " + ERR_BADCHANNELKEY);
        }
    }
    return "";
}