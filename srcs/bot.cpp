#include "../headers/server.hpp"

std :: string  get_welcome()
{
    std::string msg = BLUE;
	
	
	msg.append("██████████████████████████████████████████████████████████████████████████████████\n");
	msg.append(BLUE "█\t" RED " WELCOME TO IRC BOT" BLUE "\r\t\t\t\t\t\t\t\t\t\t █\n");
	msg.append(BLUE "█\t" RED " Usage: BOT [COMMAND_NUMBER] [MORE_OPTIONS]" BLUE "\r\t\t\t\t\t\t\t\t\t\t █\n");
	msg.append(BLUE "█\t How Can I Help You: (You can use The following list of commands)\r\t\t\t\t\t\t\t\t\t\t █\n");
	msg.append(BLUE "█\t " CYAN "[1]" RESET " : Check how many joined channels" BLUE "\r\t\t\t\t\t\t\t\t\t\t █\n");
	msg.append(BLUE "█\t " CYAN "[2]" RESET " : Check how many user online" BLUE "\r\t\t\t\t\t\t\t\t\t\t █\n");
	msg.append(BLUE "█\t " CYAN "[3]" RESET " : to List all Channels in Server" BLUE "\r\t\t\t\t\t\t\t\t\t\t █\n");
	msg.append(BLUE "█\t " CYAN "[4]" RESET " : to List Infos about the Server" BLUE "\r\t\t\t\t\t\t\t\t\t\t █\n");
	msg.append(BLUE "█                                                                                █\n");
	msg.append(BLUE "██████████████████████████████████████████████████████████████████████████████████\n\n\n\n");
	msg.append(RESET);
	return (msg);
}

std :: string server ::  get_online_user()
{
    std :: string ans = "";
    std :: map <int, client*> :: iterator it = this->_clientMap.begin();
    ans.append( RED"███████████████████████████████████████████████████████████████████████████████████████\n" RESET);
    ans.append(BLUE "ONLINE USERS: \n" RESET);
    while(it != _clientMap.end())
    {
      
        ans.append(YELLOW "user name is: " RESET);
        if(it->second->get_registration())
            ans.append(it->second->get_Nickname());
        else
            ans.append("This user is not registered yet");

        ans.append("\n-------\n");
        it++;
    }
    ans.append(GREEN "Total Online Users is: " + std :: to_string(_clientMap.size()) + "\n" RESET);
    ans.append( RED"███████████████████████████████████████████████████████████████████████████████████████\n" RESET);
    return(ans);

}


std :: string server :: list_all_channels()
{
    std :: string ans = "";
    std :: map<std :: string, Channel*> :: iterator it = _channels.begin();
    ans.append( RED"███████████████████████████████████████████████████████████████████████████████████████\n" RESET);
    ans.append(BLUE "TOTAL CHANNELS IN SERVER: \n" RESET);
    while(it != this->_channels.end())
    {
        ans.append(YELLOW "Channel name is: " GREEN);
        ans.append(it->first + "\n" RESET);
        it++;
        ans.append("-------\n");
    }
     ans.append(GREEN "Total channels is: " + std :: to_string(_channels.size()) + "\n" RESET);
     ans.append( RED"███████████████████████████████████████████████████████████████████████████████████████\n" RESET);
     return (ans);
}


std :: string server ::  srv_info()
{
    std :: string ans = "";
    ans.append( RED"███████████████████████████████████████████████████████████████████████████████████████\n" RESET);
    ans.append( BLUE "Server name : " RESET + this->_name + "\n");
    ans.append(BLUE "Total Online users: " RESET + std :: to_string (this->_online_client) + "\n");
    if(_channels.size() != 0)
        ans.append(list_all_channels());
    else
        ans.append(BLUE "Total Channels: " RESET + std :: to_string (this->_channels.size()) + "\n");
    ans.append( RED"███████████████████████████████████████████████████████████████████████████████████████\n" RESET);
    return(ans);
}

std :: string server :: bot_lunch(request req, int fd)
{
    std :: string welcome = get_welcome();
    if(req.args.size() == 0)
        return(welcome);
    else
    {
        if (req.args[0][0] == '1')
        {
            std :: string ans = "";
            int flag = 0;
            std :: map<std :: string, Channel*> :: iterator it = _channels.begin();
            ans.append( RED"███████████████████████████████████████████████████████████████████████████████████████\n" RESET);
            ans.append(BLUE "CHANNELS YOU JOINED: \n" RESET);
            for(; it != _channels.end(); it++)
            {
                if(it->second->isMember(this->_clientMap[fd]))
                {
                    ans.append(YELLOW "Channel name is: " RESET);
                    ans.append(it->second->get_name());
                    flag++;
                    ans.append("\n-------\n");
                }
                
            }
            if (flag == 0)
            {
                ans = "";
                ans.append(" " YELLOW"YOU JOINED NO CHANNEL" RESET " \n");
                return(ans);
            }
            ans.append(GREEN "Total Joined Channel is: " + std :: to_string(flag) + "\n" RESET);
            ans.append( RED"███████████████████████████████████████████████████████████████████████████████████████\n" RESET);
            return (ans);
        }
        else if(req.args[0][0] == '2')
            return(get_online_user());
        else if(req.args[0][0] == '3')
            return(list_all_channels());
        else if(req.args[0][0] == '4')
            return(srv_info());
        else{
            return("args should be 1 - 2 - 3 - 4");
        }
    }
    return("");
}