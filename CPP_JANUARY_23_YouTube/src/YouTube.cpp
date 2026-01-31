#include "YouTube.hpp"

std::unique_ptr<YouTube>& YouTube::CreatePlatform() {
    if(!Platform) Platform = std::move(std::unique_ptr<YouTube> (new YouTube));
    return Platform;
}

void YouTube::addChannel(std::string& name) {
    for (size_t i{}; i < Channels.size(); ++i){
        if (Channels[i]->getName() == name) {
            std::cout << "Channel with this name >> " << name <<  " << already exist";
            std::cout << "Please input correct name" << std::endl;
            std::cin >> name;
            i = 0;
        } 
    }
    Channels.push_back(std::unique_ptr<Channel> (new Channel(name)));
    std::cout << "Your channel successfuly added" << std::endl;
}

void YouTube::removeChannel(std::unique_ptr<Channel> channel) {
    for (size_t i{}; i < Channels.size(); ++i) {
        if(Channels[i].get() == channel.get()){
            Channels.erase(Channels.begin() + i);
            std::cout << "Channel >> " << channel->getName() << " << successfuly removed!" << std::endl;
            return;
        }
    }
    std::cout << "We haven't htis channel" << std::endl;
}
