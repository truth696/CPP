#pragma once
#include "Video.hpp"

class Creator{
public:
    virtual Video& createVideo(std::string description) = 0;
};
