#pragma once
#include <memory>
#include <vector>
#include <iostream>
#include "Channels.hpp"

class Channel;


class YouTube {
    std::unique_ptr<YouTube> Platform;
    std::vector<std::unique_ptr<Channel>> Channels;
    YouTube() = default;
public:
    static YouTube& getRoot() { static YouTube r; return r; }
    std::unique_ptr<YouTube>& CreatePlatform();
    void addChannel(std::string& name);
    void removeChannel(std::unique_ptr<Channel> channel);
};