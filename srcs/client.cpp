#include "../headers/client.hpp"

client ::client() : _clientfd(0), _is_registred(false), _is_connected(false), _NickName(), _UserName(), _FullName(), _Host("abdel_test"), _ID(), _buff(""){};
client ::client(int fd) : _clientfd(fd), _is_registred(false), _is_connected(false), _NickName(), _UserName(), _FullName(), _Host(), _ID(){};
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
    this->_ID = rhs._ID;
    this->_remotaddr = rhs._remotaddr;
    this->_addrlen = rhs._addrlen;

    return (*this);
}

client ::~client(){};


void	client::leave_channel( std::string ChannelName )
{
	this->_joinedChannels.erase(ChannelName);
};




// getters

std::string &client ::get_Buff() {return this->_buff; }
int client ::get_Clientfd() { return this->_clientfd; }
bool client ::get_registration() { return this->_is_registred; }
bool client ::get_connection() { return this->_is_connected; }
std ::string client ::get_Nickname() { return this->_NickName; }
std ::string client ::get_Username() { return this->_UserName; }
std ::string client ::get_FullName() { return this->_FullName; }
const std ::string client ::get_Host() { return this->_Host; }
std ::string client ::get_ID() { return this->_ID; }
struct sockaddr_storage client ::get_remoteaddr() { return this->_remotaddr; }
socklen_t client ::get_addrlen() { return this->_addrlen; }
struct Modes client ::get_modes() { return this->_modes; }


std::string		client::getUserPerfix() const { return (":" + this->_NickName + "!" + this->_UserName + "@" + this->_Host + " "); };

// setters

void client ::set_Clientfd(int fd) { this->_clientfd = fd; }
void client ::set_registration() { this->_is_registred = true; }
void client ::set_connection() { this->_is_connected = true; }
void client ::set_Nickname(std ::string nickName) { this->_NickName = nickName; }
void client ::set_Username(std ::string UserName) { this->_UserName = UserName; }
void client ::set_FullName(std ::string FullName) { this->_FullName = FullName; }
void client ::set_ID(std ::string id) { this->_ID = id; }
void client ::set_operator()
{
    this->_is_operator = true;
    this->_modes.op = true;
    this->_modes.localOp = true;
};
