#include "../headers/channel.hpp"

Channel::Channel()
{
    _name = "";
    _topic = "";
    _key = "";
    _creator = NULL;
    _onlineUsers = 0;
}

Channel::Channel(std::string channelName, std::string channelKey, client *Creater)
{
    _name = channelName;
    _key = channelKey;
    _creator = Creater;
    _topic = "";
    _onlineUsers = 0;
    _isinviteonly = false;
    _isPrivate = false;
    _isSecret = false;
    _isModerated = false;
    _isTopicSet = false;
    _isLimitSet = false;
    _isKeySet = false;
    _limitUsers = -1;
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
        _creator = rhs._creator;
        _onlineUsers = rhs._onlineUsers;
        _members = rhs._members;
        _operators = rhs._operators;
        _voice = rhs._voice;
    }
    return *this;
}
Channel::~Channel()
{
}

void Channel::addMember(client *newMember, int isOpertor, int isVoice)
{
    std::cout << newMember->get_Nickname() << " joined " << _name << std::endl;
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

std::pair<client *, int> Channel :: pick_user_role(int i)
{
    std::map<int, client *>::iterator it = this->_operators.find(i);
	if (it != this->_operators.end())
		return (std::pair<client *, int>(it->second, 1));
    it = this->_members.find(i);
	if (it != this->_members.end())
		return (std::pair<client *, int>(it->second, 0));
	it = this->_voice.find(i);
	if (it != this->_voice.end())
		return (std::pair<client *, int>(it->second, 2));
	return (std::pair<client *, int>(NULL, -1));
}


std :: string Channel :: get_name()
{
    return(this->_name);
}

void client ::add_channel(std ::string channelName, Channel *chanel)
{
    _joinedChannels[channelName] = chanel;
}

std::string Channel::get_key()
{
    return _key;
}

bool Channel::isMember(client *newMember)
{
    if (_members.find(newMember->get_Clientfd()) != _members.end())
        return true;
    return false;
}

int Channel::get_onlineUsers()
{
    return _onlineUsers;
}

void Channel::removeMember(client *Member)
{
    std::cout << Member->get_Nickname() << " left " << _name << std::endl;
    _members.erase(Member->get_Clientfd());
    _operators.erase(Member->get_Clientfd());
    _voice.erase(Member->get_Clientfd());
    _onlineUsers--;
}


std::string Channel::get_topic()
{
    return _topic;
}

void Channel::set_topic(std::string newTopic)
{
    _topic = newTopic;
}

std::map<int, client *>	Channel:: collect_users() const
{
	std::map<int, client *>	allUsers(this->_members.begin(), this->_members.end());
	allUsers.insert(this->_operators.begin(), this->_operators.end());
	allUsers.insert(this->_voice.begin(), this->_voice.end());
	return (allUsers);
};

void Channel::set_mode(char mode, bool status, std::string arg)
{
    if (mode == 'i')
        _isinviteonly = status;
    else if (mode == 'm')
        _isModerated = status;
    else if (mode == 'p')
        _isPrivate = status;
    else if (mode == 's')
        _isSecret= status;
    else if (mode == 't')
        _isTopicSet = status;
    else if (mode == 'k')
    {
        _isKeySet = status;
        _key = arg;
    }
    else if (mode == 'l')
    {
        _isLimitSet = status;
        _limitUsers = atoi(arg.c_str());
    }
}

bool    Channel::isOperator(client *newMember)
{
    if (_operators.find(newMember->get_Clientfd()) != _operators.end())
        return true;
    return false;
}

bool Channel::isInviteOnly()
{
    return _isinviteonly;
}

bool Channel::isKeySet()
{
    return _isKeySet;
}

bool Channel::isLimitSet()
{
    return _isLimitSet;
}

bool Channel::isPrivate()
{
    return _isPrivate;
}

bool Channel::isSecret()
{
    return _isSecret;
}

bool Channel::isModerated()
{
    return _isModerated;
}

bool Channel::isTopicSet()
{
    return _isTopicSet;
}

std::string Channel::get_modes()
{
    std::string modes = "";
    if (this->_isinviteonly == true)
        modes += "i";
    if (this->_isKeySet == true)
        modes += "k";
    if (this->_isLimitSet == true)
        modes += "l";
    if (this->_isPrivate == true)
        modes += "p";
    if (this->_isSecret == true)
        modes += "s";
    if (this->_isTopicSet == true)
        modes += "t";
    if (this->_isModerated == true)
        modes += "m";
    return (modes);
}
void Channel::add_invited_client(client *newMember)
{
    _invited.insert(std::pair<int, client *>(newMember->get_Clientfd(), newMember));
}

std::map<int, client *> &Channel::getMembers()
{
    return _members;
}

std::string Channel::getMembersNickNames()
{
    std::string members;
    std::map<int, client *>::iterator it;
    for (it = this->_members.begin(); it != this->_members.end(); it++)
    {
        if (isOperator(it->second))
            members += "@";
        members += it->second->get_Nickname();
        members += " ";
    }
    return (members);
}

void Channel::remove_from_channel(client *member)
{
    int clientFd = member->get_Clientfd();

    if (_members.find(clientFd) != _members.end())
    {
        std::cout << member->get_Nickname() << " left " << _name << std::endl;
        _members.erase(clientFd);
        _onlineUsers--;
    }
    if (_operators.find(clientFd) != _operators.end())
        _operators.erase(clientFd);
    if (_voice.find(clientFd) != _voice.end())
        _voice.erase(clientFd);
    if (_invited.find(clientFd) != _invited.end())
        _invited.erase(clientFd);
}

int Channel::get_limitUsers()
{
    return _limitUsers;
}