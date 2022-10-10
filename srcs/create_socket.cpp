#include "../headers/server.hpp"



void server :: create_socket(std :: string port)
{
    int yes = 1;
    int status;

    struct addrinfo hint, *srvInfo, *tmp;

   	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = getprotobyname("TCP")->p_proto;

	status = getaddrinfo("0.0.0.0", port.c_str(), &hint, &srvInfo);
	if (status != 0)
	{
		std::cout << "getaddrinfo() error: " << gai_strerror(status) << std::endl;
		exit(-1);
	}
	for(tmp = srvInfo; tmp != NULL; tmp = tmp->ai_next)
	{
		this->_socketFd = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
		if (this->_socketFd < 0)
			continue;

		setsockopt(this->_socketFd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

		if (bind(this->_socketFd, tmp->ai_addr, tmp->ai_addrlen) < 0)
		{
			close(this->_socketFd);
			continue;
		}
		break;
	}

	freeaddrinfo(srvInfo);

	if (tmp == NULL)
	{
		std::cout << "bind() error: " << strerror(errno) << std::endl;
		exit(-1);
	}

	if (listen(this->_socketFd, this->_max_online) == -1)
	{
		std::cout << "listen() error: " << strerror(errno) << std::endl;
		exit(-1);
	}






}
