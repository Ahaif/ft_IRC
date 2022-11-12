#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "server.hpp"

class client;

class Channel
{
private:
    char _prefix;
    client *_creator;
    int _onlineUsers;
    std::string _name;
    std::string _key;
    std::string _topic;
    std::map<int, client *>     _members;
    std::map<int, client *>     _operators;
    std::map<int, client *>     _voice;
    std::vector<std::string>    _banned;
   

private:
    Channel();

public:
    Channel(std::string ChannelName, client *Creater);
    Channel(std::string ChannelName, std::string ChannelKey, client *Creater);
    Channel(const Channel &x);
    Channel &operator=(const Channel &rhs);
    ~Channel();
    void addMember(client *newMember, int isOpertor, int isVoice);
    std::string get_key();


    std ::pair <client * , int> pick_user_role(int fd);

    std:: string    get_name();
    // void	delete_operator( int i );
	// void	delete_voice( int i );
	// void	removeBanned( std::string NickName );
	void removeMember(client *Member);
    bool isMember(client *newMember);
    int get_onlineUsers();
};

#endif