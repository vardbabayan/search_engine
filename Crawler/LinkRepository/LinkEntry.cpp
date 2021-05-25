#include "LinkEntry.hpp"

LinkEntry::LinkEntry()
    : id{}, url{}, websiteId{}, status{}, lastUpdate{}
{
}

LinkEntry::~LinkEntry()
{
}


LinkEntry::LinkEntry(const std::string& url, size_t websiteId, size_t status)
    : url{url}, websiteId{websiteId}, status{status}
{
}

size_t LinkEntry::getId() const
{
    return id;
}

std::string LinkEntry::getUrl() const
{
    return url;
}

size_t LinkEntry::getWebsiteId() const
{
    return websiteId;
}

size_t LinkEntry::getStatus() const
{
    return status;
}

std::time_t LinkEntry::getLastUpdatedTime() const
{
    return lastUpdate;
}


// LinkEntry::LinkEntry(const std::string& url, int status, const std::time_t& lastUpdate)
//     : url{url}, status{status}, lastUpdate{lastUpdate}
// {
// }

// LinkEntry::LinkEntry(const std::string& url, int websiteId, int status, const std::time_t& lastUpdate)
//     : url{url}, websiteId{websiteId}, status{status}, lastUpdate{lastUpdate}
// {
// }

// LinkEntry::LinkEntry(int id, const std::string& url, int websiteId, int status, const std::time_t& lastUpdate)
//     : id{id}, url{url}, websiteId{websiteId}, status{status}, lastUpdate{lastUpdate}
// {
// }