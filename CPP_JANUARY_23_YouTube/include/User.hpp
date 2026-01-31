#pragma once
#include "Channels.hpp"
#include <memory>
#include <vector>

class Channel;

class User : public std::enable_shared_from_this<User> {
    std::vector<std::shared_ptr<Channel>> channels;
public:
    void subscribe(std::shared_ptr<Channel> ch);
    void unsubscribe(std::shared_ptr<Channel> ch);
    void notify();
};