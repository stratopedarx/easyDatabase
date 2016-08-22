#include <exception>
#include <stdexcept>
#include <iostream>
#include "cmdclient.h"


CMDClient::CMDClient(Server *pS)
    : lastReq(RequestType::UNKNOWN, "", ""),
      lastAnsw(RequestType::UNKNOWN, AnswerType::NON, "")
{
    pServer = pS;
}


void CMDClient::readCMD()
{
    std::cout << "Enter please the command in format "
                 << "COMMAND:<KEY>=[VALUE] "
                 << "Use --help or -h for the help information: " << std::endl;
    std::cin >> rawCMD;
    if (rawCMD == "--help" || rawCMD == "-h")
    {
        std::cout << "1. SAVE:<KEY>=[VALUE]" << std::endl;
        std::cout << "2. FIND:<KEY>" << std::endl;
        std::cout << "3. REMOVE:<KEY>" << std::endl;
        std::cout << "Enter please the command: " << std::endl;
        std::cin.sync();    // clean the buffer
        std::cin >> rawCMD;
    }
    if(rawCMD == "exit")    // close the application
        exit(0);
}


void CMDClient::parseCMD()  // std::string rawCMD_
{
    // parse from rawCMD

    RequestType rType = RequestType::UNKNOWN;   // default value
    std::string rKey = "<key>";                 // default value
    std::string rValue = "[value]";             // default value

    if(rawCMD.empty())
    {
        throw std::runtime_error("Raw CMD is empty");
    }

    // parse the Type
    int typePosition = rawCMD.find(":");
    if(typePosition != std::string::npos)
    {
        std::string sType = rawCMD.substr(0, typePosition);
        std::cout << sType << std::endl;
        if (sType == "SAVE")
            rType = RequestType::SAVE;
        else if(sType == "FIND")
            rType = RequestType::FIND;
        else if(sType == "REMOVE")
            rType = RequestType::REMOVE;
        else if(sType == "UNKNOWN")
            throw std::runtime_error("Cannot parse request type!");
        else
            throw std::runtime_error("The command is not correct. Cannot parse request type!");
    }

    // parse the key and the value
    std::string command = rawCMD.substr(typePosition + 1, rawCMD.length());
    if(rType == RequestType::SAVE)
    {
        int keyPosition = command.find("=");
        if(keyPosition != std::string::npos)
        {
            rKey = command.substr(0, keyPosition);
            std::cout << rKey << std::endl;
        }
        rValue = command.substr(keyPosition + 1, command.length());
    }
    else
        rKey = command;

    // make user request
    Request req(rType, rKey, rValue);
    lastReq = req;
}


void CMDClient::handleReq()
{
     lastAnsw = pServer->exec(lastReq);
}


void CMDClient::setServer(Server* s)
{
    pServer = s;
}


Answer CMDClient::typeCMD()
{
    readCMD();
    parseCMD();
    handleReq();
    return lastAnsw;
}
