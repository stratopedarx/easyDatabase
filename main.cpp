#include <iostream>
#include "cmdclient.h"
#include "server.h"

using namespace std;

int main(int argc, char *argv[])
{
    Server server("db.txt");    // cteate server
    CMDClient client(&server);  // create client with server
    //client.setServer(&server);

    Answer answ = client.typeCMD();
    std::cout << (int)answ.answer << ":" << (int)answ.request << "=" << answ.value;
    return 0;
}
