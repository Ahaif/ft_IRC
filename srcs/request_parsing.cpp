#include "../headers/server.hpp"

request server ::split_msg(std ::string msg)
{
    request req;
    int i = 0;
    int j = 0;
    int flag = 0;

    if (msg[i] == ' ' || !msg[i])
    {
        req.invalidMsg = true;
        return (req);
    }
    j = i;
    while (msg[i] != '\0' && msg[i] != '\r' && msg[i] != '\n')
    {
        if (msg[i] == ' ')
        {
            if (msg[i - 1] && msg[i - 1] != ' ')
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
            if (msg[i] && msg[i - 1] != ' ')
            {
                req.invalidMsg = true;
                return (req);
            }
            std ::cout << "msg size is: " << msg.length() << std ::endl;
            int res = msg.length() - 1;
            req.args.push_back(msg.substr(i + 1, res));

            req.cmd = req.args[0];
            req.args.erase(req.args.begin());
            if (flag > 1)
            {
                std ::cout << "error prefix args should be last parms" << std ::endl;
                exit(-1);
            }
            return (req);
        }
        if (msg[i] == '\0')
            break;
        i++;
    }
    if (msg[j] && i)
        req.args.push_back(msg.substr(j, i - j));
    if (req.args.size() > 0)
    {
        req.cmd = req.args[0];
        req.args.erase(req.args.begin());
    }
    return (req);
}

bool    cmd_contain(std :: string msg)
{

        if(msg[msg.size() -1] == 10)
            return (true);
        else
            return(false);
}

std ::string server ::parse_request(std ::string msg, int clientFd)
{
    client *clnt = _clientMap[clientFd];
    std::string prefix = ":" + _name + " ";
    std::string nick = clnt->get_Nickname();

    // if(!cmd_contain(msg))
    //     return("");

    std::string tmp(msg);
    request req(split_msg(tmp));
    // std :: cout << "req.args.size() is: " << req.args.size() << std :: endl;
    // std ::cout << "Cmd req is : " << req.cmd << std ::endl;
    // std ::cout << "-----------------" << std ::endl;
    // for (unsigned long i = 0; i < req.args.size(); i++)
    // {
    //     std ::cout << "Args requests : " << req.args[i] << std ::endl;
    // }
    // std ::cout << "-----------------" << std ::endl;
    if (req.cmd == "PASS")
        return (set_pssw(req, clientFd));
    else if (req.cmd == "NICK")
        return (registerName(req, clientFd));
    else if (req.cmd == "USER")
        return (set_userName(req, clientFd));
    else if (req.cmd == "OPER")
        return (set_Oper(req, clientFd));
    else if (req.cmd == "MODE")
        return (mode_command(req, clientFd));
    else if (req.cmd == "INVITE")
        return (invite_command(req, clientFd));
    else if (req.cmd == "NAMES")
        return (names_command(req, clientFd));
    else if (req.cmd == "LIST")
        return (list_command(req, clientFd));
    else if (req.cmd == "PRIVMSG")
        return (prvmsg(req, clientFd));
    else if (req.cmd == "NOTICE")
        return (notice_command(req, clientFd));
    else if (req.cmd == "JOIN")
        return (join_chnl(req, clientFd));
    else if (req.cmd == "TOPIC")
        return (this->topic_command(req, clientFd));
    else if (req.cmd == "KICK")
        return (kick_user(req, clientFd));
    else if (req.cmd == "PART")
        return (part_command(req, clientFd));
    else if (req.cmd == "QUIT")
    {
        remove_from_poll(clientFd);
        return "";
    }
    else if (req.cmd == "SENDFILE")
        return (" execute Pass CMD");
    else if (req.cmd == "GETFILE")
        return (" execute Pass CMD");
    else if (req.cmd == "BOT")
        return (bot_lunch(req, clientFd));
    else if (req.cmd == "PONG")
        return ("");
    else
    {
        send_replay1(clnt, prefix, "421", nick, req.cmd + " " + ERR_UNKNOWNCOMMAND);
        return ("");
    }
}