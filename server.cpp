#include "server.h"


Server::Server(std::string path)
{
    dbFilePath = path;
    std::cout << "Server instance created for " << dbFilePath << std::endl;
}

void Server::readFile()
{
    std::cout << "read file" << dbFilePath << std::endl;
}


void Server::writeFile()
{
    std::cout << "write file" << dbFilePath << std::endl;
}


bool Server::keyExists(std::string key)
{
    std::cout << "key exist" << std::endl;
}


void Server::addRecord(Record record)
{
    std::cout << "ADD:" << record.first << record.second << std::endl;
}


Record Server::findRecord(std::string key)
{
    std::cout << "FIND:" << key << std::endl;
}


void Server::removeRecord(std::string key)
{
    std::cout << "REMOVE:" << key << std::endl;
}

Answer Server::exec(Request r)
{
    Answer answer(RequestType::SAVE, AnswerType::OK, "OK-OK");
    readFile();
    switch(r.type)
    {
        case RequestType::SAVE :
        std::cout << "handle save" << std::endl;

        if (keyExists(r.key))
        {
            std::cout << "Key already exists" <<std::endl;
        }
        else
        {
            std::cout << "addinf key - value" << std::endl;
            Record record(r.key, r.value);
            addRecord(record);
        }
        break;

        case RequestType::FIND :
        std::cout << "handle find" << std::endl;
        findRecord(r.key);
        break;

        case RequestType::REMOVE :
        std::cout << "handle remove" << std::endl;
        removeRecord(r.key);
        break;

        default:
        std::cout << "ERROR: unknown CMD" << std::endl;
        break;
    }
    return answer;
}
