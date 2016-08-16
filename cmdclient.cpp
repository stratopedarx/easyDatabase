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
    std::cin >> rawCMD;
}


void CMDClient::parseCMD()  // std::string rawCMD_
{
    // parse from rawCMD

    RequestType rType = RequestType::UNKNOWN;
    std::string rKey = "<key>";
    std::string rValue = "[value]";


    if(rawCMD.empty())
    {
        throw std::runtime_error("Raw CMD is empty");
    }
    std::string temp;

    int typePosition = rawCMD.find(":");
    if(typePosition != std::string::npos)
    {
        std::string sType = rawCMD.substr(0, typePosition);
        std::cout << sType << std::endl;
        if (sType == "SAVE")
        {
            rType = RequestType::SAVE;
        }
        if (sType == RequestType::UNKNOWN)
        {
            throw std::runtime_error("Cannot parse request type!");
        }
    }
    Request req(rType, rKey, rValue);
    lastReq = req;
}


void CMDClient::handleReq()
{
     lastAnsw = pServer->exec(lastReq);
}


Answer CMDClient::typeCMD()
{
    readCMD();
    parseCMD();
    handleReq();
    return lastAnsw;
}


void CMDClient::setServer(Server* s)
{
    pServer = s;
}
