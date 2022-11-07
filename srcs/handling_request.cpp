#include "../headers/server.hpp"

void server ::handle_request(int position, client *client)
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
		buf[nbytes] = '\0';
		client->get_Buff().append(buf);
	}
	if (buf[nbytes - 1] == '\n')
	{
		std::cout << client->get_Buff();
		std::string ret = parse_request(client->get_Buff(), clientFd);
		std ::cout << ret << std ::endl;
		client->get_Buff().erase();
	}
}
