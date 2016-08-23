#ifndef SERVER_H
#define SERVER_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "answer.h"
#include "cmdclient.h"

class CMDClient;
typedef std::pair<std::string, std::string> Record;


class Server
{
    std::string dbFilePath;
    std::vector<Record> data;
    void readFile();
    void writeFile();
    bool keyExists(std::string key);
    void addRecord(Record);             // add record to the data/DataBase
    Record findRecord(std::string key); // find needed record in the data
    void removeRecord(std::string key); // remove the record from the data
    void eraseData();

public:
    Server(std::string path);
    Answer exec(Request r);
};

#endif // SERVER_H
