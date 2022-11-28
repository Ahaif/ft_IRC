#include "../headers/server.hpp"

std ::string server ::set_pssw(request req, int fd)
{
	if (req.args.size() < 1)
	{
		return (format_msg("461", "PASS",  ERR_NEEDMOREPARAMS));
	}
	if (this->_clientMap[fd]->get_registration())
	{
		return (format_msg("462", _clientMap[fd]->get_Nickname(),  ERR_ALREADYREGISTERED));
	}
	if (strcmp(req.args[0].c_str(), this->_password.c_str()) == 0)
	{
		this->_clientMap[fd]->set_connection();
	}
	else
	{
		return (format_msg("464", _clientMap[fd]->get_Nickname(),  ERR_PASSWDMISMATCH));
	}
	return ("");
}

std ::string server ::registerName(request req, int fd)
{
	if (!this->_clientMap[fd]->get_connection())
		return ("You should connect first with PASS cmd\n");
	else if (req.args.size() < 1)
	{
		return (":No nickname given\n");
	}
	for(size_t k = 0; k < req.args.size(); k++)
	{
		for (long unsigned int j = 0; j < req.args[k].size(); j++)
		{
			if (!isalnum(req.args[k][j]) && req.args[k][j] != '-' && req.args[k][j] != '\r')
				return (format_msg("432", req.args[k], ERR_ERRONEUSNICKNAME));
		}
	}

	if (std::find(this->_clientName.begin(), this->_clientName.end(), req.args[0]) != this->_clientName.end())
	{
			if (req.args.size() == 2)
				req.args.erase(req.args.begin());
			else
				return (format_msg("433", _clientMap[fd]->get_Nickname(), ERR_NICKNAMEINUSE));
	}
	this->_clientMap[fd]->set_Nickname(req.args[0]);
	this->_clientName.push_back(this->_clientMap[fd]->get_Nickname());
	if (this->_clientMap[fd]->get_Username() != "")
	{
		this->_clientMap[fd]->set_connection();
		return (format_msg("001", _clientMap[fd]->get_Nickname(),RPL_WELCOME));
	}

	return ("");
};


int		server::_find_FdBy_NickName(std::string NickName)
{
	std::map<int, client *>::iterator it = this->_clientMap.begin();
	while(it != this->_clientMap.end())
	{
		if (it->second->get_Nickname() == NickName)
			return (it->second->get_Clientfd());
		it++;
	}
	return (-1);
}

std ::string server ::set_userName(request req, int fd)
{
	if (!this->_clientMap[fd]->get_connection())
		return ("You need to authenticate first");
	if (this->_clientMap[fd]->get_registration())
	{
		return (format_msg("462", _clientMap[fd]->get_Nickname(), ERR_ALREADYREGISTERED));
	}
	if (req.args.size() < 4)
	{
		return (format_msg("461", _clientMap[fd]->get_Nickname(), ERR_NEEDMOREPARAMS));
	}
	this->_clientMap[fd]->set_Username(req.args[0]);
	this->_clientMap[fd]->set_FullName(req.args[3]);
	this->_clientMap[fd]->set_registration();
	if (_clientMap[fd]->get_Nickname() != "")
	{
		this->_clientMap[fd]->set_connection();
		return (format_msg("001", _clientMap[fd]->get_Nickname(),RPL_WELCOME));
	}
	return ("");
}

std ::string server ::set_Oper(request req, int fd)
{
	if (!this->_clientMap[fd]->get_registration())
		return ("You have not registered");
	if (req.args.size() < 2)
		return (format_msg("461", _clientMap[fd]->get_Nickname(), ERR_NEEDMOREPARAMS));
	if (req.args[0] != "ADMIN")
		return (format_msg("464", _clientMap[fd]->get_Nickname(),  ERR_PASSWDMISMATCH));
	if (req.args[1] != "abdel")
		return (format_msg("464", _clientMap[fd]->get_Nickname(),  ERR_PASSWDMISMATCH));
	_clientMap[fd]->set_operator();
	return (format_msg("381", this->_clientMap[fd]->get_Nickname(), ":You are now an IRC operator"));
}

static bool param_contain(std ::string &param, char op)
{
	for (unsigned long i = 0; i < param.length(); i++)
	{
		if (param[i] == op)
			return true;
	}
	return (false);
}

static bool valid_mode(std ::string &modeParam)
{
	if (modeParam[0] != '-' && modeParam[0] != '+')
		return false;
	if (modeParam[1] != 'i' && modeParam[1] && 's' && modeParam[1] != 'w' && modeParam[1] != 'o')
		return false;
	return true;
}

std ::string client ::set_mode(std::string param)
{
	bool val;
	if (param[0] == '-')
		val = false;
	else
		val = true;
	if (param[1] == 'i')
		this->_modes.invisible = val;
	if (param[1] == 'o')
		this->_modes.op = val;
	if (param[1] == 's')
		this->_modes.server = val;
	if (param[1] == 'w')
		this->_modes.wallops = val;
	if (param[1] == 'r' && val)
		this->_modes.restricted = val;
	if (param[1] == 'O' && val)
		this->_modes.localOp = val;
	// std :: cout << "NEW MODE for user is: " <<  this->_modes.invisible <<std :: endl;
	return ("user mode set successfly.... ");
}

std ::string server ::set_user_mode(request req, int fd)
{
	if (!this->_clientMap[fd]->get_registration())
		return (format_msg("451", "", ":You have not registered"));
	if (req.args.size() != 2 || req.args[1].length() != 2)
		return (format_msg("461", _clientMap[fd]->get_Nickname(), ERR_NEEDMOREPARAMS));
	if (req.args[0] != _clientMap[fd]->get_Nickname())
		return (format_msg("502", this->_clientMap[fd]->get_Nickname(), ":Cannot change mode for other users"));
	else
	{
		if (param_contain(req.args[1], 'o') && param_contain(req.args[1], '+'))
			return ("");
		std ::cout << "MODE is: " << req.args[1] << std ::endl;
		if (valid_mode(req.args[1]))
		{
			this->_clientMap[fd]->set_mode(req.args[1]);
			return(format_msg("221", this->_clientMap[fd]->get_Nickname(), req.args[1]));
		}
	}
	return ("");
}
