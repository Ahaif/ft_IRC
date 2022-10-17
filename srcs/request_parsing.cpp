#include "../headers/server.hpp"


request server :: split_msg(std :: string  msg)
{
    request req;
    int i = 0;
    int j = 0;
    int flag = 0;

    if (msg[i] == ' ' || !msg[i]) {
		req.invalidMsg = true;
		return (req);
	}
    j = i;
    
    while(msg[i] != '\r' && msg[i] != '\n')
    {
        if (msg[i] == ' ')
        {
            if (i == 0) 
            {
                req.invalidMsg = true;
		        return (req);
            }
            if(msg[i - 1] && msg[i- 1] != ' ')
            {
                req.args.push_back(msg.substr(j, i - j));
                while (msg[i] == ' ')
				    i++;
                j = i;
            }
        }
        if (msg[i] == ':')
        {
            flag++;
            if (msg[i] && msg[i -1] != ' ')
            {
                req.invalidMsg = true;
		        return (req);
            }
            req.args.push_back(msg.substr(i + 1, msg.length()));
            req.cmd = req.args[0];
            req.args.erase(req.args.begin());
            if(flag > 1)
            {
                std :: cout << "error prefix args should be last parms"  << std :: endl;
                exit(-1);
            }
            return(req);
        }
        i++;
    }
    if(msg[j] && i)
        req.args.push_back(msg.substr(j, i - j));
    req.cmd = req.args[0];
    req.args.erase(req.args.begin());

    return(req);
}


std :: string server :: parse_request(std :: string msg, int clientFd)
{
    request req(split_msg(msg));
    std :: cout << "Cmd req is : " << req.cmd << std :: endl;
    std :: cout << "-----------------" << std :: endl;
    for(unsigned long i = 0; i < req.args.size(); i++)
    {
        std :: cout << "Args requests : " << req.args[i] << std :: endl;
    }
    std :: cout << "-----------------" << std :: endl;
    if (req.invalidMsg)
		return ("Invalid message!\n");
	if (req.cmd == "PASS")
		return (set_pssw(req,clientFd));
	else if (req.cmd == "NICK")
		return (registerName(req, clientFd));
	else if (req.cmd == "USER")
		return (set_userName(req, clientFd));
	else if (req.cmd == "OPER")
		return (set_Oper(req,clientFd));
	else if (req.cmd == "MODE")
		return (set_user_mode(req, clientFd));
    else if (req.cmd == "INVITE")
        return("Channel operation invite");
    else if (req.cmd == "NAMES")
        return("Channel operation names");
    else if (req.cmd == "LISTS")
        return("Channel operation lists");
	else if (req.cmd == "PRIVMSG")
		return (" execute Pass CMD");
	else if (req.cmd == "NOTICE")
		return (" execute NOTICE CMD");
	// else if (req.cmd == "HELP")
	// 	return (" execute Pass CMD");
	else if (req.cmd == "JOIN")
		return (join_chnl(req, clientFd));
	else if (req.cmd == "TOPIC")
	    return (" execute Pass CMD");
	else if (req.cmd == "KICK")
		return (" execute Pass CMD");
	else if (req.cmd == "PART")
		return (" execute Pass CMD");
	// else if (req.cmd == "QUIT")
	// 	return ("quit command execute");
	else if (req.cmd == "SENDFILE")
		return (" execute Pass CMD");
	else if (req.cmd == "GETFILE")
		return (" execute Pass CMD");
	else if (req.cmd == "BOT")
		return (" execute  CMD");
	else
		return ("Invalid cmd\n");

}