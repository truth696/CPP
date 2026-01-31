#pragma once 
#include <string>

class Video{
protected:
    std::string type;
    std::string description;
public:
    Video(std::string inptype, std::string inpdisc) : type(inptype), description(inpdisc) {}
    virtual ~Video() = default;
    virtual std::string getType() = 0;
    virtual std::string getDescription() = 0;
};