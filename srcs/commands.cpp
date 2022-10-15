#include "../headers/server.hpp"


std :: string server :: set_pssw(request req, int fd)
{
	if (req.args.size() < 1)
		return("PASS error Args\n");
	if(this->_clientMap[fd]->get_registration())
		return("Client already registred\n");
	if(req.args[1] != this->_password)
		return("Password incorrect\n");
	else
		this->_clientMap[fd]->set_connection();
	
	return ("");

}

std :: string server :: registerName(request req, int fd)
{
    if(!this->_clientMap[fd]->get_connection())
        return( "You should connect first with PASS cmd\n");
    else if(req.args.size() < 1)
        return ("Number of Args is no correct\n");
    for(long unsigned int j =0; j < req.args[0].size(); j++)
    {
        if (!isalnum(req.args[0][j]) && req.args[0][j] != '-' && req.args[0][j] != '\r')
            return("Error Nickname syntaxe");
    }
	if (std::find(this->_clientName.begin(), this->_clientName.end(), req.args[0]) != this->_clientName.end())
		return ("Nickname is already in use");

	this->_clientMap[fd]->set_Nickname(req.args[0]);
	this->_clientName.push_back(this->_clientMap[fd]->get_Nickname());
	if (this->_clientMap[fd]->get_Username() != "") {
		this->_clientMap[fd]->set_ID(this->_clientMap[fd]->get_Nickname() + "!" + this->_clientMap[fd]->get_Username() + "@" + this->_clientMap[fd]->get_Host());
		this->_clientMap[fd]->set_connection();
		return ("Welcome to the Internet Relay Network ");
	}
	return ("");
};

std :: string server :: set_userName(request req, int fd)
{
	if(!this->_clientMap[fd]->get_connection())
		return("You need to authenticate first");
	if(!this->_clientMap[fd]->get_registration())
		return("User already registred...");
	if (req.args.size() < 4)
		return("Error size args...");
	this->_clientMap[fd]->set_Username(req.args[0]);
	this->_clientMap[fd]->set_FullName(req.args[4]);
	if (this->_clientMap[fd]->get_Username() != "") 
	{
		this->_clientMap[fd]->set_ID(this->_clientMap[fd]->get_Nickname() + "!" + this->_clientMap[fd]->get_Username() + "@" + this->_clientMap[fd]->get_Host());
		this->_clientMap[fd]->set_connection();
		return ("Welcome to the Internet Relay Network ");
	}
	return ("");
	
}