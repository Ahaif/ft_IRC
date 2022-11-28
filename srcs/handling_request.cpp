#include "../headers/server.hpp"

void server ::handle_request(int position)
{
	char buf[5000];
	static std :: string rest;
	int clientFd = _pfds[position].fd;
	int nbytes = recv(clientFd, buf, sizeof(buf), 0);
	if (nbytes <= 0)
	{
		if (nbytes == 0)
			std::cout << "["
					  << "currentDateTime"
					  << "]: socket " << clientFd << " hung up" << std::endl;
		else
			std::cout << "recv() error: " << strerror(errno) << std::endl;

		close(clientFd);
		remove_from_poll(clientFd);
	}
	else
	{
		buf[nbytes] = 0;
		if(buf[strlen(buf) -1] != 10 && buf[strlen(buf) - 1] != 127)
		{
			rest = strdup(buf);
		}
		else
		{
			std::string message;
			if (rest.size() != 0)
			{
				message.append(rest);
				rest.clear();
			}
			message.append(buf);
			if (message[message.size()- 1] ==  '\r')
				message.erase(message.size() - 1);
			std::string ret = parse_request(message, clientFd);
			if(ret.size())
			{
				if (send(clientFd, ret.c_str(), ret.length(), 0) == -1)
					std::cout << "send() error: " << strerror(errno) << std::endl;
			}
			
		}
	}
	memset(&buf, 0, 5000);
}
