
#ifndef REQUEST_HPP
#define REQUEST_HPP


#include "server.hpp"

class request
{
    public:
        std :: string                   cmd;
        std :: vector<std :: string>    args;
        bool                            invalidMsg;
    public:
        request();
        request(const request &x);
        request & operator = ( const request &rhs );
        ~request();
};

#endif