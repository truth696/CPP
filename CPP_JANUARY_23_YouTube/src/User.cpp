#include "User.hpp"

void User::subscribe(std::shared_ptr<Channel> ch) {
    if(!(ch->subscribe(shared_from_this()))){
        std::cout << "You already subscribed" << std::endl;
        return;
    } else{
        channels.push_back(ch);
        std::cout << "Successfuly!" << std::endl;
    }
}

void User::unsubscribe(std::shared_ptr<Channel> ch) {
    if(!(ch->unsubscribe(shared_from_this()))){
        std::cout << "You don't subscribed on channel" << std::endl;
    } else{
        for (size_t i{}; i < channels.size(); ++i){
            if (channels[i].get() == ch.get()) {
                channels.erase(channels.begin() + i);
                std::cout << "Successfuly!" << std::endl;
                return;
            }
        }
        std::cout << "You don't subscribe on channel" << std::endl;
    }
}

void User::notify() {
    std::cout << "You have a new notification from channel" << std::endl;
}