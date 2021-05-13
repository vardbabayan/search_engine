#include "LinkEntry.hpp"

LinkEntry::LinkEntry()
    : id{}, url{}, websiteId{}, status{}, lastUpdate{}
{
}


LinkEntry::LinkEntry(const std::string& url, int status, const std::time_t& lastUpdate)
    : url{url}, status{status}, lastUpdate{lastUpdate}
{
}

LinkEntry:: LinkEntry(int id, const std::string& url, int status, const std::time_t& lastUpdate) 
    : url{url}, websiteId{websiteId}, status{status}, lastUpdate{lastUpdate}
{
}

LinkEntry::LinkEntry(int id, const std::string& url, int websiteId, int status, const std::time_t& lastUpdate)
    : id{id}, url{url}, websiteId{websiteId}, status{status}, lastUpdate{lastUpdate}
{
}

std::string LinkEntry::getUrl()
{
    return url;
}

int LinkEntry::getWebsiteId()
{
    return websiteId;
}

int LinkEntry::getStatus()
{
    return status;
}

std::time_t LinkEntry::getLastUpdatedTime()
{
    return lastUpdate;
}
