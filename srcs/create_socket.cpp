#include "../headers/server.hpp"



void server :: create_socket(std :: string port)
{
    int enable = 1;

	this->_socketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_socketFd < 0)
	{
		std::cerr << "Create socket failed" << std::endl;
		exit(-1);
	}
	if (setsockopt(this->_socketFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)))
	{
		std::cerr << "Setsockopt failed" << strerror(errno) << std::endl;
		exit(-1);
	}
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(atoi(port.c_str()));
	if (bind(this->_socketFd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		std::cerr << "bind failed" << strerror(errno) << std::endl;
		exit(-1);
	}
	if (listen(this->_socketFd, _online_client) < 0)
	{
		std::cerr << "listen failed" << strerror(errno) << std::endl;
		exit(-1);
	}
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	time_t tt = std::chrono::system_clock::to_time_t(now);
	start_time = ctime(&tt);
	start_time.erase(start_time.find("\n"), 1);
}
