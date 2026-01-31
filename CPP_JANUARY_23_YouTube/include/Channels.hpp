#pragma once
#include "Video.hpp"
#include "ShortVideo.hpp"
#include "RegularVideo.hpp"
#include "LiveStream.hpp"
#include <memory>
#include <vector>
#include <string>
#include <iostream>

class User;

class Channel {
    std::string name;
    std::vector<std::shared_ptr<User>> subscribers;
    std::vector<std::shared_ptr<Video>> short_videos;
    std::vector<std::shared_ptr<Video>> regular_videos;
    std::vector<std::shared_ptr<Video>> stream_records;
    bool unique_video(std::shared_ptr<Video> v);
    void notify_subscribers();
public:
    Channel(std::string name) : name (name) {}
    bool subscribe(std::shared_ptr<User> p);
    bool unsubscribe(std::shared_ptr<User> p);
    void addVideo(std::shared_ptr<Video> v);
    void deleteVideo(std::shared_ptr<Video> v);
    inline std::string getName() const noexcept { return name; }
};