#include "../headers/server.hpp"

void server ::handle_request(int position)
{
	// split request
	char buf[5000];

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
		std::string message(buf, strlen(buf) - 1);
		if (message[message.size()- 1] ==  '\r')
			message.erase(message.size() - 1);
		std::string ret = parse_request(message, clientFd);
		if(ret.size())
		{
			if (send(clientFd, ret.c_str(), ret.length(), 0) == -1)
			std::cout << "send() error: " << strerror(errno) << std::endl;
			std ::cout << ret << std ::endl;
		}
	}
}
