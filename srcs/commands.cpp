#include "../headers/server.hpp"


std :: string server :: set_pssw(request req, int fd)
{
	if (req.args.size() < 1)
		return("PASS error Args\n");
	if(this->_clientMap[fd]->get_registration())
		return("Client already registred\n");


	// std :: cout << "client passord is|" << req.args[0]<<"|"<< std :: endl;
	// std :: cout << "server passord is|" << this->_password<<"|"<< std :: endl;
	
	if(strcmp(req.args[0].c_str(), this->_password.c_str()) == 0)
	{
		this->_clientMap[fd]->set_connection();
		return("PASSWORD set succesfuly");
	}
	else
		return("Password incorrect why \n");
	
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
		return ("-------Welcome to the Internet Relay Network---------");
	}
	return ("Nick Name setup  succesfly ");
};

std :: string server :: set_userName(request req, int fd)
{
	if(!this->_clientMap[fd]->get_connection())
		return("You need to authenticate first");
	if(this->_clientMap[fd]->get_registration())
		return("User already registred...");
	if (req.args.size() < 4)
		return("Error size args...");

	this->_clientMap[fd]->set_Username(req.args[0]);
	this->_clientMap[fd]->set_FullName(req.args[4]);
	this->_clientMap[fd]->set_registration();
	if (this->_clientMap[fd]->get_Username() != "") 
	{
		this->_clientMap[fd]->set_ID(this->_clientMap[fd]->get_Nickname() + "!" + this->_clientMap[fd]->get_Username() + "@" + this->_clientMap[fd]->get_Host());
		this->_clientMap[fd]->set_connection();
		return ("--------Welcome to the Internet Relay Network-------");
	}
	return ("");
	
}


std :: string server :: set_Oper(request req, int fd)
{
	if (!this->_clientMap[fd]->get_registration())
		return ( "You have not registered");
	if (req.args.size() < 2)
		return ("Not enough parameters");
	if (req.args[0] != "ADMIN")
		return ( "Usernameincorrect");
	if (req.args[1] != "abdel")
		return ( "Password incorrect");
	_clientMap[fd]->set_operator();
	return ( "You are now an IRC operator");


}


static bool param_contain(std :: string &param, char op)
{
	for(unsigned long i = 0; i < param.length(); i++)
	{
		if(param[i] == op)
			return true;
	}
	return(false);
}

static bool valid_mode(std :: string & modeParam)
{
	if(modeParam[0] != '-' && modeParam[0] != '+')
		return false;
	if(modeParam[1] != 'i' && modeParam[1] && 's' && modeParam[1] != 'w' && modeParam[1] != 'o')
		return false;
	return true;
}

std :: string client ::  set_mode(std:: string param)
{
	bool val;
	if(param[0] == '-')
		val = false;
	else
		val = true;
	if(param[1] == 'i')
		this->_modes.invisible = val;
	if(param[1] == 'o')
		this->_modes.op = val;
	if(param[1] == 's')
		this->_modes.server = val;
	if(param[1] == 'w')
		this->_modes.wallops = val;
	if(param[1] == 'r' && val)
		this->_modes.restricted = val;
	if (param[1] == 'O' && val)
		this->_modes.localOp = val;
	// std :: cout << "NEW MODE for user is: " <<  this->_modes.invisible <<std :: endl;
	return ("user mode set successfly.... ");
}

std :: string server ::	set_user_mode(request req, int fd)
{
	if(!this->_clientMap[fd]->get_registration())
		return("You are not registred.");
	if(req.args.size() != 2 || req.args[1].length() != 2)
		return("param size error for Mode cmd ");
	if(req.args[0] != _clientMap[fd]->get_Nickname())
		return("MODE cmd should have have the same nickname...");
	else
	{
		if (param_contain(req.args[1], 'o') && param_contain(req.args[1], '+'))
			return("");
		std :: cout << "MODE is: " << req.args[1] << std :: endl;
		if(valid_mode(req.args[1]))
		{
			
			return(this->_clientMap[fd]->set_mode(req.args[1]));
		}
	}
	return("");
}