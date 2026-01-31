#include "RegularVideoCreator.hpp"

Regular_Video& CreatorRegularVideo::createVideo(std::string description) {
    Regular_Video* p = new Regular_Video(description);
    return *p;
}