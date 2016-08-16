#include "request.h"

Request::Request(RequestType rt, std::string key, std::string value)
{
    type = rt;
    this->key = key;
    this->value = value;
    std::cout << "Request created" << (int)type << ":" << this->key << "=" << this->value << std::endl;
}
