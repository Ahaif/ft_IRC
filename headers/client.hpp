#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "server.hpp"
// #include "channel.hpp"

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
		std::string							_ID;
		struct sockaddr_storage				_remotaddr;
		socklen_t							_addrlen;
        struct Modes                        _modes;

        //add Modes data as struct
		//add map fpr joined channel
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
        bool                    get_is_operator();
        std :: string           get_Nickname();
        std :: string           get_Username();
        std :: string           get_FullName();
        const std :: string     get_Host();
        std :: string           get_ID();
        struct sockaddr_storage get_remoteaddr();
        socklen_t               get_addrlen();
        struct Modes            get_modes();

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
        void    set_ID(std :: string id);
        void    set_remoteaddr(struct sockaddr_storage rmAdress);
        void    set_addrlen(socklen_t addLen);
        void    set_operator();
        std :: string   set_mode(std :: string);
        void    leave_channel(std :: string chanelId);
        void    leave_all_chnl();
        void    add_invited_channel(std :: string channelName, Channel *chanel);
    //function to check if the client is joined to a channel 

};


#endif