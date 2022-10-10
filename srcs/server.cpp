#include "../headers/server.hpp"




server :: server(std :: string name, int max_online, std :: string port, std:: string password)
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

void server :: start_server()
{
    while(42)
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
					// If listener is ready to read, handle new connection
				
					// If not the listener, we're just a regular client
			}
		}
	}
        
}