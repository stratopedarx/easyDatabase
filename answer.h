#ifndef ANSWER_H
#define ANSWER_H
#include <string>
#include "request.h"
#include <iostream>


enum class AnswerType{
    OK,
    FAIL,
    NON
};

class Answer
{
public:
    Answer(RequestType rT, AnswerType aT, std::string value)
    {
        request = rT;
        answer = aT;
        value = value;
        std::cout << "Answer cteated " << (int)rT << ":" << (int)aT << "=" << value << std::endl;
    }
    RequestType request;
    AnswerType answer;
    std::string value;
};

#endif // ANSWER_H
