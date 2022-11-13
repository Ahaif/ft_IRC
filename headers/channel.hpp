#ifndef CHANNEL_HPP
#define CHANNEL_HPP




#define	USERALREADYJOINED 0
#define USERISJOINED 1
#define NOTINCHANNEL 2
#define BANNEDFROMCHAN 3
#define TOOMANYCHANNELS 4
#define BADCHANNELKEY 5
#define CHANNELISFULL 6
#define NOSUCHCHANNEL 7
#define USERISBANNED 8
#define BADCHANMASK 9
#define USERNOTINCHANNEL -1
#define USERNOTFOUND -1

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
	void            removeMember(client *Member);
    bool            isMember(client *newMember);
    int             get_onlineUsers();
    std::string     get_topic();
    void            set_topic(std::string newTopic);
    int             add_Operator( client *member );
    void            print_Operatorchnl();
    int            memberSize();
};

#endif