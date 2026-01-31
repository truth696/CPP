#include "Channels.hpp"
#include "User.hpp"

void Channel::notify_subscribers() {
    for (auto user: subscribers) user->notify();
}

bool Channel::unique_video(std::shared_ptr<Video> v){
    if (dynamic_cast<Short_Video*> (v.get())){
        for (size_t i{}; i < short_videos.size(); ++i) {
            if (short_videos[i].get() == v.get()) return false;
        }
    } else if (dynamic_cast<Regular_Video*> (v.get())){
        for (size_t i{}; i < regular_videos.size(); ++i) {
            if (regular_videos[i].get() == v.get()) return false;
        }
    } else if (dynamic_cast<Live_Stream*> (v.get())){
        for (size_t i{}; i < stream_records.size(); ++i) {
            if (stream_records[i].get() == v.get()) return false;
        }
    }
    return true;
}

bool Channel::subscribe(std::shared_ptr<User> p){
    for (size_t i{}; i < subscribers.size(); ++i) {
        if (subscribers[i].get() == p.get()) {
            return false;
        }
    }
    subscribers.push_back(std::move(p));
    return true;
}

bool Channel::unsubscribe(std::shared_ptr<User> p){
    for (size_t i{}; i < subscribers.size(); ++i) {
        if (subscribers[i].get() == p.get()) {
            subscribers.erase(subscribers.begin() + i);
            return true;
        }
    }
    return false;   
}

void Channel::addVideo(std::shared_ptr<Video> v){
    if (!unique_video(v)) {
        std::cout << "This video already posted" << std::endl;
        return;
    }
    std::cout << "Your >>" << v->getType() << " successfully posted" << std::endl;
    if (!(v->getDescription().empty())) std::cout << "Description >> " << v->getDescription();
    if (dynamic_cast<Short_Video*>(v.get())) short_videos.push_back(std::move(v));
    else if (dynamic_cast<Regular_Video*>(v.get())) regular_videos.push_back(std::move(v));
    else if (dynamic_cast<Live_Stream*>(v.get())) stream_records.push_back(std::move(v));
    notify_subscribers();
}

void Channel::deleteVideo(std::shared_ptr<Video> v){
    if (unique_video(v)){
        std::cout << "You cannot delete video, which haven't own you" << std::endl;
        return;
    }
    if (dynamic_cast<Short_Video*>(v.get())){
        for (size_t i{}; i < short_videos.size(); ++i){
            if (v.get() == short_videos[i].get()){
                short_videos.erase(short_videos.begin() + i);
                std::cout << "Successfully!" << std::endl;
            }
        }
    }
    else if (dynamic_cast<Regular_Video*>(v.get())) {
        for (size_t i{}; i < regular_videos.size(); ++i){
            if (v.get() == regular_videos[i].get()){
                regular_videos.erase(regular_videos.begin() + i);
                std::cout << "Successfully!" << std::endl;
            }
        }
    }
    else if (dynamic_cast<Live_Stream*>(v.get())){
        for (size_t i{}; i < stream_records.size(); ++i){
            if (v.get() == stream_records[i].get()){
                stream_records.erase(stream_records.begin() + i);
                std::cout << "Successfully!" << std::endl;
            }
        }
    }
}


