#include "LinkEntry.hpp"

LinkEntry::LinkEntry()
    : id{}, url{}, websiteId{}, status{}, lastUpdate{}
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