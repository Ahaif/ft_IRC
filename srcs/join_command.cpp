#include "../headers/server.hpp"

std ::string server ::join_chnl(request req, int fd)
{
    std::vector<std::string> names;
    std::vector<std::string> keys;
    if (!this->_clientMap[fd]->get_registration())
        send_replay(_clientMap[fd], "451", ERR_NOTREGISTERED);
    else if (req.args.size() == 0)
        send_replay(_clientMap[fd], "461", ERR_NEEDMOREPARAMS);
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
                send_replay(_clientMap[fd], "403", ERR_NOSUCHCHANNEL);
            else
            {
                _channels[names[i]] = new Channel(names[i], keys[i], _clientMap[fd]);
                _channels[names[i]]->addMember(_clientMap[fd], 1, 1);
                send_replay(this->_clientMap[fd], " is joining the channel", ":" + names[i] + "\n");
            }
        }
        else if (this->_channels[names[i]]->get_key() == keys[i])
        {
            this->_channels[names[i]]->addMember(_clientMap[fd], 0, 0);
            send_replay(this->_clientMap[fd], "JOIN", ":" + names[i] + "\n");
        }
        else
            send_replay(this->_clientMap[fd], "475", ERR_BADCHANNELKEY);
    }
    return "";
}