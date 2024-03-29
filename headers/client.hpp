#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "server.hpp"
// #include "channel.hpp"


# define GREEN "\e[1;32m"
# define RESET "\e[0m"
# define RED "\e[1;91m"
# define CYAN "\e[1;36m"
# define YELLOW "\e[1;33m"
# define PURPLE "\e[1;35m"
# define BLUE "\e[1;34m"


struct Modes
{
	bool	away;
	bool	invisible;
	bool	wallops;
	bool	restricted;
	bool	op;
	bool	localOp;
	bool	server;
};

class Channel;

class client
{
    private:
        int                                 _clientfd;
        bool                                _is_registred;
        bool                                _is_connected;
        bool                                _is_operator;
        std :: string                       _NickName;
        std :: string                       _UserName;
        std :: string                       _FullName;
        const std::string					_Host;
        struct Modes                        _modes;
        std :: map<std :: string, Channel *>         _joinedChannels;
        std :: map<std :: string, Channel *>         _invitedChannels;

    public:
        client();
        client(int fd);
        client(const client & x);
        ~client();
        client & operator= (const client & rhs);
    
    //getters
    public :
        int                     get_Clientfd();
        bool                    get_registration();
        bool                    get_connection();
        std :: string           get_Nickname();
        std :: string           get_Username();
        std :: string           get_FullName();
        const std :: string     get_Host();
        std::string		getUserPerfix() const;

    //setters
    public:
        void    set_Clientfd(int fd);
        void    set_registration();
        void    set_connection();
        void    set_Nickname(std :: string nickName);
        void    set_Username(std :: string userName);
        void    set_FullName(std :: string fullName);
        void    set_Host(const std :: string host);
        void    set_operator();
        std :: string   set_mode(std :: string);
        void    add_invited_channel(std :: string channelName, Channel *chanel);
        bool    isHasNoChannel();
        void    part_from_channel(Channel *channel);
        void    add_channel(std :: string channelName, Channel *chanel);
        bool    is_invited_to(Channel *invitedChannel);
};


#endif