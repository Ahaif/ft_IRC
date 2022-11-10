#include "../headers/server.hpp"


std::vector<std::string> server::comma_sep(std :: string chnlist)
{
    std::vector<std::string> ret;
	size_t pos = 0;
	while ((pos = chnlist.find(",")) != std::string::npos)
	{
		ret.push_back(chnlist.substr(0, pos));
		chnlist.erase(0, pos + 1);
	}
	ret.push_back(chnlist.substr(0, pos));
	return (ret);
}







std::string	server ::_partCmd( request request, int i )
{
	if (!this->_clientMap[i]->get_registration())
		return (" You have not registered");
	if (request.args.size() != 2)
		return (" ERR_NEEDMOREPARAMS ");
	std::vector<std::string>	channelsParsed(comma_sep(request.args[0]));
	std::vector<std::string>::iterator it = channelsParsed.begin();
	while (it != channelsParsed.end())
	{
		int j = 0;
		if (request.args.size() == 2)
        {
            std::map<std::string, Channel *>::iterator itCh= this-> _channels.find(*it);
	        if (itCh == this->_channels.end() /* No such channel */)
		        return ("NOSUCHCHANNEL");
            else
            {
                std::pair<client *, int> user(itCh->second->pick_user_role(i));
                if (user.second == -1 /* Not in channel */)
                    return ("NOTINCHANNEL");
                else
                {
                    if (user.second == 0)
                        itCh->second->delete_member(i);
                    else if(user.second == 1)
                        itCh->second->delete_operator(i);
                    else
                        itCh->second->delete_voice(i);
                    //apply leave channel 
                }
                

            }

        }

	return ("");
};


