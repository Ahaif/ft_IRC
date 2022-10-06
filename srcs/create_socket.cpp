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
		std::cout << "getaddrinfo() error: " << std::endl;
		exit(-1);
	}






}
