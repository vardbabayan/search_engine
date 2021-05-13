#ifndef LINK_ENTRY
#define LINK_ENTRY

#include <ctime>
#include <string>
#include "LinkStatus.hpp"

class LinkEntry 
{
public:    
    int id;
    std::string url;
    int websiteId;
    int status;
    std::time_t lastUpdate;

    LinkEntry();
    LinkEntry(const std::string& url, int status, const std::time_t& lastUpdate);
    LinkEntry(int id, const std::string& url, int status, const std::time_t& lastUpdate);
    LinkEntry(int id, const std::string& url, int websiteId, int status, const std::time_t& lastUpdate);

    int getId();
    std::string getUrl();
    int getWebsiteId();
    int getStatus();
    std::time_t getLastUpdatedTime();
};

#endif
