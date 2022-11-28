#include "../headers/client.hpp"

client ::client() : _clientfd(0), _is_registred(false), _is_connected(false), _NickName(), _UserName(), _FullName(), _Host("abdel_test"){};
client ::client(int fd) : _clientfd(fd), _is_registred(false), _is_connected(false), _NickName(), _UserName(), _FullName(), _Host(){};
client ::client(const client &x) : _Host("abdel_test") { *this = x; };

client &client ::operator=(const client &rhs)
{
    if (this == &rhs)
        return (*this);
    this->_clientfd = rhs._clientfd;
    this->_is_registred = rhs._is_registred;
    this->_is_connected = rhs._is_connected;
    this->_NickName = rhs._NickName;
    this->_UserName = rhs._UserName;
    this->_FullName = rhs._FullName;
    return (*this);
}

client ::~client(){};

// getters

int client ::get_Clientfd() { return this->_clientfd; }
bool client ::get_registration() { return this->_is_registred; }
bool client ::get_connection() { return this->_is_connected; }
std ::string client ::get_Nickname() { return this->_NickName; }
std ::string client ::get_Username() { return this->_UserName; }
std ::string client ::get_FullName() { return this->_FullName; }
const std ::string client ::get_Host() { return this->_Host; }


std::string		client::getUserPerfix() const { return (":" + this->_NickName + "!" + this->_UserName + "@" + this->_Host + " "); };

// setters

void client ::set_Clientfd(int fd) { this->_clientfd = fd; }
void client ::set_registration() { this->_is_registred = true; }
void client ::set_connection() { this->_is_connected = true; }
void client ::set_Nickname(std ::string nickName) { this->_NickName = nickName; }
void client ::set_Username(std ::string UserName) { this->_UserName = UserName; }
void client ::set_FullName(std ::string FullName) { this->_FullName = FullName; }
void client ::set_operator()
{
    this->_is_operator = true;
    this->_modes.op = true;
    this->_modes.localOp = true;
};

void client::add_invited_channel(std ::string channelName, Channel *chanel)
{
    _invitedChannels[channelName] = chanel;
}
bool client ::isHasNoChannel()
{
    if (this->_joinedChannels.size() == 0)
        return (true);
    return (false);
}
void    client::part_from_channel(Channel *channel)
{
    std::string channelName = channel->get_name();

    if(_joinedChannels.find(channelName) != _joinedChannels.end())
        _joinedChannels.erase(channelName);
    if (_invitedChannels.find(channelName) != _invitedChannels.end())
        _invitedChannels.erase(channelName);
}

bool client::is_invited_to(Channel *invitedChannel)
{
    std::map<std::string, Channel *>::iterator it = _invitedChannels.begin();

    for (; it != _invitedChannels.end(); it++)
    {
        if (it->first == invitedChannel->get_name())
            return true;
    }
    return false;
}