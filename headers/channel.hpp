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
    std::map<int, client *>     _invited;
    bool _isinviteonly;
    bool _isPrivate;
    bool _isSecret;
    bool _isModerated;
    bool _isTopicSet;
    bool _isLimitSet;
    bool _isKeySet;
    int _limitUsers;

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

    std:: string                get_name();
    std::map<int, client *>	    collect_users() const;
    // void	delete_operator( int i );
	// void	delete_voice( int i );
	// void	removeBanned( std::string NickName );
	void            removeMember(client *Member);
    bool            isMember(client *newMember);
    bool            isOperator(client *newMember);
    int             get_onlineUsers();
    std::string     get_topic();
    void            set_topic(std::string newTopic);
    int             add_Operator( client *member );
    void            print_Operatorchnl();
    int            memberSize();
    bool            isInviteOnly();
    bool            isPrivate();
    bool            isSecret();
    bool            isModerated();
    bool            isTopicSet();
    bool            isLimitSet();
    bool            isKeySet();
    std::string     get_modes();
    void add_invited_client(client *newMember);
    void            set_mode(char mode, bool status, std::string arg);
    std::map<int, client *> &getMembers();
    std::string getMembersNickNames();
    void remove_from_channel(client *member);
};

#endif