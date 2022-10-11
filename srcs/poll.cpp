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
    this->_online_client++;


}