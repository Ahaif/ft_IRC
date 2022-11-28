#include "../headers/server.hpp"

void server :: add_to_poll(int fd)
{
    if (this->_online_client == this->_max_online)
    {
        this->_max_online = this->_online_client * 2;
        this->_pfds = (struct pollfd *)realloc(this->_pfds, this->_max_online);
    }
    this->_pfds[this->_online_client].fd = fd;
    this->_pfds[this->_online_client].events = POLLIN;
    this->_clientMap.insert(std ::pair<int, client *>(fd, new client(fd)));
    this->_online_client++;
}

void server ::remove_from_poll(int fd)
{
    client *clnt = _clientMap[fd];
    std::vector<std::string>::iterator it = _clientName.begin();
    for (; it != _clientName.end(); it++)
    {
        if (*it == this->_clientMap[fd]->get_Nickname())
        {
            _clientName.erase(it);
            break;
        }
    }
    std::map<std::string, Channel *>::iterator it2 = _channels.begin();
    std::map<std::string, Channel *>::iterator next = it2;
    while (it2 != _channels.end())
    {
        next++;
        if (it2->second->isMember(clnt) == true)
            send_to_allUsers(_channels[it2->first], fd, "PART " + it2->first + " :\n", false);
        it2->second->remove_from_channel(clnt);
        if (it2->second->get_onlineUsers() == 0)
        {
            Channel *tmp = it2->second;
            _channels.erase(it2);
            delete tmp;
        }
        it2 = next;
    }
    this->_clientMap.erase(fd);
    for (int i = 0; i < this->_online_client; i++)
    {
        if (this->_pfds[i].fd == fd && i != 0)
        {
            this->_pfds[i].fd = this->_pfds[this->_online_client - 1].fd;
            this->_pfds[i].events = this->_pfds[this->_online_client - 1].events;
            this->_pfds[i].revents = this->_pfds[this->_online_client - 1].revents;
            this->_online_client--;
            break;
        }
    }
    delete clnt;
    close(fd);
}