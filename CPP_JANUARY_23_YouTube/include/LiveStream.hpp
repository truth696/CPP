#pragma once
#include "Video.hpp"

class CreatorLiveStream;

class Live_Stream : public Video {
private:
    Live_Stream(std::string description = std::string{}) : Video("LiveStream", description) {}
public:
    virtual std::string getType() override { return type; }
    virtual std::string getDescription() override { return description; }
    friend CreatorLiveStream;
};