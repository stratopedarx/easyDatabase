#ifndef CMDCLIENT_H
#define CMDCLIENT_H
#include <string>
#include <iostream>
#include "request.h"
#include "answer.h"
#include "server.h"

class Server;

class CMDClient
{
private:
    Server* pServer;    // the pointer on the linked server
    Request lastReq;
    Answer lastAnsw;
    std::string rawCMD;
    void readCMD();
    void parseCMD();
    void handleReq();

public:
    CMDClient(Server *pS);
    void setServer(Server* s);
    Server* getServer();
    Answer typeCMD();
};

#endif // CMDCLIENT_H
