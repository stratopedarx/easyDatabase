#ifndef REQUEST_H
#define REQUEST_H
#include <string>
#include <iostream>


enum class RequestType{
    SAVE,
    FIND,
    REMOVE,
    UNKNOWN
};


class Request
{
public:
    Request(RequestType rt, std::string key, std::string value);
    RequestType type;
    std::string key;
    std::string value;
};

#endif // REQUEST_H
