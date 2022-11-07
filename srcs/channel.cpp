#include "../headers/channel.hpp"

Channel::Channel()
{
    _name = "";
    _topic = "";
    _key = "";
    _prefix = '#';
    _creator = NULL;
    _onlineUsers = 0;
}

Channel::Channel(std::string channelName, client *Creater)
{
    _name = channelName;
    _topic = "";
    _key = "";
    _prefix = '#';
    _creator = Creater;
    _onlineUsers = 0;
}
Channel::Channel(std::string channelName, std::string channelKey, client *Creater)
{
    _name = channelName;
    _key = channelKey;
    _creator = Creater;
    _topic = "";
    _prefix = '#';
    _onlineUsers = 0;
}
Channel::Channel(const Channel &x)
{
    *this = x;
}
Channel &Channel::operator=(const Channel &rhs)
{
    if (this != &rhs)
    {
        _name = rhs._name;
        _topic = rhs._topic;
        _key = rhs._key;
        _prefix = rhs._prefix;
        _creator = rhs._creator;
        _onlineUsers = rhs._onlineUsers;
        _members = rhs._members;
        _operators = rhs._operators;
        _voice = rhs._voice;
        _banned = rhs._banned;
    }
    return *this;
}
Channel::~Channel()
{
}

void Channel::addMember(client *newMember, int isOpertor, int isVoice)
{
    _members[newMember->get_Clientfd()] = newMember;
    if (isOpertor)
    {
        _operators[newMember->get_Clientfd()] = newMember;
        newMember->set_operator();
    }
    else if (isVoice)
        _voice[newMember->get_Clientfd()] = newMember;
    _onlineUsers++;
}

std::string Channel::get_key()
{
    return _key;
}