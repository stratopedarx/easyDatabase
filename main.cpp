#include <iostream>
#include "cmdclient.h"
#include "server.h"

using namespace std;

int main(int argc, char *argv[])
{
    Server server("/home/stratopedarx/Documents/niit/po/labs/DataBase/c_plus/DataBase/data.txt");    // cteate server
    CMDClient client(&server);  // create client with server

    while('loop')
    {
        Answer answ = client.typeCMD();
        std::cout << (int)answ.answer << ":" << (int)answ.request << "=" << answ.value;
    }
    return 0;
}
