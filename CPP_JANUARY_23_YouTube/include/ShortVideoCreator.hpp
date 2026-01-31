#pragma once
#include "VideoCreator.hpp"
#include "ShortVideo.hpp"

class CreatorShortVideo : public Creator{
public:
    Short_Video& createVideo(std::string description) override ;
};
