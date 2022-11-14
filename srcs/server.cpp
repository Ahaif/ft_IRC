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
	clientFD = accept(this->_socketFd, (struct sockaddr *) &remotaddr, &addrlen);
	if (clientFD == -1)
		std::cout << "accept() error: " << strerror(errno) << std::endl;
	else
	{
		add_to_poll(clientFD);
		std::string welcome = "First Connection This is a Welcome MSG\n";
		if (send(clientFD, welcome.c_str(), welcome.length(), 0) == -1)
			std::cout << "send() error: " << strerror(errno) << std::endl;
		std::cout << "new connection from "
				  << inet_ntoa(((struct sockaddr_in *)&remotaddr)->sin_addr)
				  << " on socket " << clientFD << std::endl;
	}
}

void server ::start_server()
{
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
				if (this->_pfds[i].fd == this->_socketFd) //
					new_connection();
				else
					handle_request(i, _clientMap.at(_pfds[i].fd));
			}
		}
	}
}

server::~server()
{
	if (this->_pfds)
		delete[] this->_pfds;
}

void server::send_replay(client *client, std::string replayNb, std::string replay)
{
	std::string message = client->get_Nickname();

	if (message == "")
		message = "*";
	message = message + " " + replayNb + " " + replay;
	write(client->get_Clientfd(), message.c_str(), message.size());
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
    }
	return (args);
}

std::string	server ::_printMessage(std::string num, std::string nickname, std::string message)
{
	if (nickname.empty())
		nickname = "*";
	return (":" + this->_name + " " + num + " " + nickname + " " + message + "\n");
}


int :: server :: list_Cnickname()
{
	int i =0;
	for(; i < (int)this->_clientMap.size(); i++)
	{
		std :: cout << _clientMap[i]->get_Nickname() << std :: endl;
	}
	return(i);
}