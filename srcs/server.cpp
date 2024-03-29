#include "../headers/server.hpp"

server ::server(std ::string name, int max_online, std ::string port, std::string password)
{
	this->_max_online = max_online;
	this->_name = name;
	this->_password = password;
	this->_pfds = new struct pollfd[max_online];
	this->_online_client = 0;
	create_socket(port);
	this->_pfds[0].fd = this->_socketFd;
	this->_pfds[0].events = POLLIN;
	this->_online_client++;
}

void server ::new_connection()
{
	struct sockaddr_storage remotaddr;
	socklen_t addrlen;
	int clientFD;

	addrlen = sizeof(remotaddr);
	clientFD = accept(this->_socketFd, (struct sockaddr *)&remotaddr, &addrlen);
	if (clientFD == -1)
		std::cout << "accept() error: " << strerror(errno) << std::endl;
	else
	{
		add_to_poll(clientFD);
		std::cout << "new connection from "
				  << inet_ntoa(((struct sockaddr_in *)&remotaddr)->sin_addr)
				  << " on socket " << clientFD << std::endl;
	}
}

void server ::start_server()
{
	std::cout << "Waiting for connections..." << std::endl;
	while (42)
	{
		int poll_count = poll(this->_pfds, this->_online_client, -1);
		if (poll_count == -1)
		{
			std::cout << "poll() error: " << strerror(errno) << std::endl;
			exit(-1);
		}
		for (int i = 0; i < this->_online_client; i++) // loop over the pool aray to find the ready fd
		{
			if (this->_pfds[i].revents & POLLIN)
			{
				if (this->_pfds[i].fd == this->_socketFd)
					new_connection();
				else
					handle_request(i);
			}
		}
	}
}

server::~server()
{
	if (this->_pfds)
		delete[] this->_pfds;
		std::map<int, client *>::iterator it = this->_clientMap.begin();
		while (it != this->_clientMap.end())
		{
			delete it->second;
			it++;
		}
		this->_clientMap.clear();
		std::map<std::string, Channel *>::iterator itC = this->_channels.begin();
		while (itC != this->_channels.end())
		{
			delete itC->second;
			itC++;
		}
		this->_channels.clear();
}

std::vector<std::string> server::split(std::string str, std::string sep)
{
	std::vector<std::string> args;
	size_t start = 0;
	size_t found = !std::string::npos;
	while (found != std::string::npos)
	{
		found = str.find(sep, start);
		args.push_back(str.substr(start, found - start));
		start = found + sep.length();
		while(str[start] == ' ')
			start++;
	}
	if(args[args.size() - 1].empty())
		args.pop_back();
	return (args);
}

std::string server ::format_msg(std::string num, std::string nickname, std::string message)
{
	if (nickname.empty())
		nickname = "*";
	return (":" + this->_name + " " + num + " " + nickname + " " + message + "\n");
}


void server::send_replay(client *client, std::string prefix, std::string replayNb, std::string nick, std::string replay)
{
	std::string message = "";

	if (nick.empty())
		nick = "*";
	message =  prefix + replayNb + " " + nick;
	if (!replay.empty())
		message += " " + replay;
	message += "\r\n";
	write(client->get_Clientfd(), message.c_str(), message.size());
}

void server::send_welcome_msg(int fd)
{
	client *clnt = _clientMap[fd];
	std::string prefix = ":" + _name + " ";
	std::string nick = clnt->get_Nickname();
	std::string message = "Welcome to the Internet Relay Network " + clnt->getUserPerfix();
	send_replay(clnt, prefix, "001", nick, message);
	message = "Your host is " + _name + ", running version 1.0";
	send_replay(clnt, prefix, "002", nick, message);
	message = "This server was created " + start_time;
	send_replay(clnt, prefix, "003", nick, message);
}
