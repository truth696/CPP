#pragma once
#include "Video.hpp"

class CreatorShortVideo;

class Short_Video : public Video {
private:
    Short_Video(std::string description = "") : Video("ShortVideo", description) {}
public:
    virtual std::string getType() override { return type; }
    virtual std::string getDescription() override { return description; }
    friend CreatorShortVideo;
};