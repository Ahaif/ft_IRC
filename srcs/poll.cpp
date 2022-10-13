#include "../headers/server.hpp"



void server :: add_to_poll(int fd)
{
    if (this->_online_client == this -> _max_online)
    {
        this->_max_online = this->_online_client * 2;
       this->_pfds = (struct pollfd *)realloc(this->_pfds, this->_max_online);
    }
    this->_pfds[this->_online_client].fd = fd;
    this->_pfds[this->_online_client].events = POLL_IN;
    // add new client to map
    this->_clientMap.insert(std :: pair<int, client*>(fd, new client(fd)));
    this->_online_client++;
}

void server :: remove_from_poll(int fd)
{
    close(this->_pfds[fd].fd);
	this->_pfds[fd] = this->_pfds[this->_online_client - 1];
    //delete client from map
    this->_clientMap.erase(this->_pfds[fd].fd);
	this->_online_client--;
}