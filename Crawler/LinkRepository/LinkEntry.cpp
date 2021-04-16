#include "LinkEntry.hpp"

LinkEntry::LinkEntry()
    : url{}, domain{}, status{}, lastUpdate{}
{
}

LinkEntry::LinkEntry(std::string url, std::string domain, LinkStatus status, std::time_t lastUpdate) 
    : url{url}, domain{domain}, status{status}, lastUpdate{lastUpdate}
{
}

std::string LinkEntry::getUrl()
{
    return url;
}

std::string LinkEntry::getDomain()
{
    return domain;
}

LinkStatus LinkEntry::getStatus()
{
    return status;
}

std::time_t LinkEntry::getLastLoadedTime()
{
    return lastUpdate;
}
