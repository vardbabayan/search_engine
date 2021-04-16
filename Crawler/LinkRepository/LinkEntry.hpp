#ifndef LINK_ENTRY
#define LINK_ENTRY

#include <ctime>
#include <chrono>
#include <string>
#include "LinkStatus.hpp"

class LinkEntry 
{
public:    
    std::string url;
    std::string domain;
    LinkStatus status;
    std::time_t lastUpdate;

    LinkEntry();
    
    LinkEntry(std::string url, std::string domain, LinkStatus status, std::time_t lastUpdate);

    std::string getUrl();
    std::string getDomain();
    LinkStatus getStatus();
    std::time_t getCreatedTime();
    std::time_t getLastLoadedTime();
};

#endif
