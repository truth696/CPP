#pragma once
#include "VideoCreator.hpp"
#include "RegularVideo.hpp"

class CreatorRegularVideo: public Creator {
public:  
    Regular_Video& createVideo(std::string description) override;
};
