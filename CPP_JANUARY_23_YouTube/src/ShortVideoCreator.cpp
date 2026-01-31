#include "ShortVideoCreator.hpp"


Short_Video& CreatorShortVideo::createVideo(std::string description) {
    Short_Video* p = new Short_Video(description);
    return *p;
}