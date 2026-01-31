#pragma once
#include "Video.hpp"

class CreatorRegularVideo;

class Regular_Video : public Video{
private:
    Regular_Video(std::string description = "") : Video("RegularVideo", description) {}
public:
    virtual std::string getType() override { return type; }
    virtual std::string getDescription() override { return description; }
    friend CreatorRegularVideo;
};