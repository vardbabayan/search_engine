#include "WebSite.hpp"

WebSite::WebSite(const std::string& domain, const std::string& homePage, std::time_t time)
    : domain{domain}, homePage{homePage}, lastCrawleTime{time}
{
}

std::string WebSite::getDomain()
{
    return domain;
}

std::string WebSite::getHomePage()
{
    return homePage;
}

std::time_t WebSite::getLastCrawleTime()
{
    return lastCrawleTime;
}