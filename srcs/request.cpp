#include "../headers/request.hpp"

request :: request() : cmd(), args(), invalidMsg(false){};
request::request( const request& x ) { *this = x; };
request::~request() {};

request & request::operator= ( const request& rhs )
{
	if (this == &rhs)
		return (*this);
	this->args = rhs.args;
	this->cmd = rhs.cmd;
	this->invalidMsg = rhs.invalidMsg;
	return (*this);
};
