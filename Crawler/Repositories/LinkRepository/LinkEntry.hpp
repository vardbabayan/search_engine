#ifndef LINK_ENTRY
#define LINK_ENTRY

#include <ctime>
#include <string>
#include "LinkStatus.hpp"

class LinkEntry 
{
public:    
    size_t id;
    std::string url;
    size_t websiteId;
    size_t status;
    std::time_t lastUpdate;

    LinkEntry();
    ~LinkEntry();
    LinkEntry(const std::string& url, size_t websiteId, size_t status);

    size_t getId() const;
    std::string getUrl() const;
    size_t getWebsiteId() const;
    size_t getStatus() const;
    std::time_t getLastUpdatedTime() const;
};

#endif