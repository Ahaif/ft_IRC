#include "../headers/server.hpp"


void server ::  handle_request(int clientFd)
{
    //split request
    char buf[5000];
	memset(&buf, 0, 5000);
	int nbytes = recv(this->_pfds[clientFd].fd, buf, sizeof(buf), 0);

	if (nbytes <= 0)
	{
		if (nbytes == 0)
			std::cout << "[" << "currentDateTime" << "]: socket " << this->_pfds[clientFd].fd << " hung up" << std::endl;
		else
			std::cout << "recv() error: " << strerror(errno) << std::endl;

		close(this->_pfds[clientFd].fd);
		remove_from_poll(this->_pfds[clientFd].fd);
	}
	else
	{
		std::string message(buf, strlen(buf) - 1);
		if (message.back() == '\r')
			message.erase(message.end() - 1);
		std::string ret = parse_request(message, this->_pfds[clientFd].fd);


		std :: cout << ret << std :: endl;
	}
}	
