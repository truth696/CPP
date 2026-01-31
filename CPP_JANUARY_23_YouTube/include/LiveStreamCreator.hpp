#pragma once
#include "VideoCreator.hpp"
#include "LiveStream.hpp"

class CreatorLiveStream : public Creator{
public:
    Live_Stream& createVideo(std::string description) override;
};
