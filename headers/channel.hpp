#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "server.hpp"
#include "client.hpp"


class channel
{
    private:
        std :: string               _topicId;
        std :: map<int, client*>    _chnlMembers;
        std :: map<int, client*>    _chnlOperators;
        client*                     _creator;

    public:
        channel();
        channel(std ::string topic, int fd);
        ~channel();
        channel(const channel & x);
        channel & operator = (const channel & rhs);


};


#endif