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


int	Channel::add_Operator( client *member )
{
	if (std::find(this->_banned.begin(), this->_banned.end(), member->get_Nickname()) != this->_banned.end())
		return (BANNEDFROMCHAN);
	if (this->_operators.find(member->get_Clientfd()) == this->_operators.end())
	{
		this->_operators.insert(std::pair<int, client *>(member->get_Clientfd(), member));
		this->_onlineUsers++;
		return (USERISJOINED);
	};
	return (-1);
};


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


void :: Channel :: print_Operatorchnl()
{
    std::map<int, client *> :: iterator it; 
    for(it = this->_operators.begin(); it != this->_operators.end(); it++)
    {
        std :: cout << "Operator is : " << it->second->get_Nickname() << std :: endl;

    }
}

int :: Channel :: memberSize()
{
    if(this->_members.size() == 0)
        return (0);
    else
        return(this->_members.size());
}

// void	Channel:: delete_operator( int i)
// {
// 	this->_operators.erase(i);
// 	this->_onlineUsers--;
// };

// void	Channel:: delete_voice( int i)
// {
// 	this->_voice.erase(i);
// 	this->_onlineUsers--;
// };

// void	Channel::removeBanned( std::string NickName )
// {
// 	if (std::find(this->_banned.begin(), this->_banned.end(), NickName) != this->_banned.end())
// 		return ;
// 	this->_banned.erase(std::find(this->_banned.begin(), this->_banned.end(), NickName));
// };

// void	Channel:: delete_member( int i)
// {
// 	this->_members.erase(i);
// 	this->_onlineUsers--;
// };



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
    _members.erase(Member->get_Clientfd());
    _operators.erase(Member->get_Clientfd());
    _voice.erase(Member->get_Clientfd());
    _onlineUsers--;
    std::cout << "Channel: " << _name << " has " << _onlineUsers << " users" << std::endl;
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