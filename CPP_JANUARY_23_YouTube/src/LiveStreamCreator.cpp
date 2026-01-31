#include "LiveStreamCreator.hpp"

Live_Stream& CreatorLiveStream::createVideo(std::string description) {
    Live_Stream* p = new Live_Stream(description);
    return *p;
}