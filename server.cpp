#include <iterator>
#include <fstream>
#include <stdexcept>
#include "server.h"


Server::Server(std::string path)
{
    dbFilePath = path;
    std::cout << "Server instance created for " << dbFilePath << std::endl;
}


void Server::readFile()
{
    std::ifstream fin(dbFilePath);   // to open a file for reading
    if (!fin)
        throw std::runtime_error("ERROR: The file doesn't open for reading");

    std::string tempStr;
    while(!fin.eof())
    {
        getline(fin,tempStr);
        if(tempStr == "") continue;
        std::cout << tempStr << std::endl;
        int keyPosition = tempStr.find("=");
        data.push_back(make_pair(
                           tempStr.substr(0, keyPosition),
                           tempStr.substr(keyPosition + 1, tempStr.length())));
    }
    fin.close();
    std::cout << "The file was read " << dbFilePath << std::endl;
}


void Server::writeFile()
{
    std::ofstream fout(dbFilePath);
    if (!fout)
        throw std::runtime_error("ERROR: The file doesn't open for writing");

    std::vector<Record>::iterator iter = data.begin();
    while(iter != data.end())
    {
        fout << iter->first << "=" << iter->second << '\n';
        ++iter;
    }
    fout.close();
    std::cout << "The file was written " << dbFilePath << std::endl;
}


bool Server::keyExists(std::string key)
{
    std::vector<Record>::iterator iter;
    for(iter = data.begin(); iter != data.end(); ++iter)
        if(iter->first == key)
        {
            std::cout << "The key exist" << std::endl;
            return true;
        }
    std::cout << "The key doesn't exist" << std::endl;
    return false;
}


void Server::addRecord(Record record)
{
    data.push_back(make_pair(record.first, record.second));
    std::cout << "ADD:" << record.first << "=" << record.second << std::endl;
}


Record Server::findRecord(std::string key)
{
    std::vector<Record>::iterator iter;
    for(iter = data.begin(); iter != data.end(); ++iter)
        if(iter->first == key)
        {
            std::cout << "FIND:" << iter->first << "=" << iter->second << std::endl;
            return Record(iter->first, iter->second);
        }
    throw std::runtime_error("ERROR: Can't find the key");
}


void Server::removeRecord(std::string key)
{
    std::vector<Record>::iterator iter;
    for(iter = data.begin(); iter != data.end(); ++iter)
        if(iter->first == key)
        {
            data.erase(iter);
            std::cout << "REMOVE:" << key << std::endl;
        }
}

Answer Server::exec(Request r)
{
    Answer answer(r.type, AnswerType::NON, "");
    readFile(); // fill the data
    switch(r.type)  // SAVE or REMOVE or FIND
    {
        case RequestType::SAVE:
            std::cout << "handle save" << std::endl;

            if (keyExists(r.key))
            {
                std::cout << "Key already exists" <<std::endl;
            }
            else
            {
                std::cout << "adding key - value" << std::endl;
                Record record(r.key, r.value);
                addRecord(record);
                try
                {
                    writeFile();
                }
                catch(std::exception const& e)
                {
                    std::cout << "Exception: " << e.what() << std::endl;
                    answer.answer = AnswerType::FAIL;
                    break;
                }
                answer.answer = AnswerType::OK;
                answer.value = r.value;
            }
            break;

        case RequestType::FIND:
            std::cout << "handle find" << std::endl;

            try
            {
                findRecord(r.key);
            }
            catch (std::exception const& e)
            {
                std::cout << "Exception: " << e.what() << std::endl;
                answer.answer = AnswerType::FAIL;
                break;
            }
            answer.answer = AnswerType::OK;
            answer.value = r.value;
            break;

        case RequestType::REMOVE:
            std::cout << "handle remove" << std::endl;
            if (keyExists(r.key))
            {
                removeRecord(r.key);
                writeFile();
                std::cout << "The Key and the value were deleted" <<std::endl;
                answer.answer = AnswerType::OK;
                answer.value = r.value;
                break;
            }
            else
            {
                std::cout << "The key doesn't exist" <<std::endl;
                answer.answer = AnswerType::FAIL;
                break;
            }

        default:
            std::cout << "ERROR: unknown CMD" << std::endl;
            break;
    }
    return answer;
}
