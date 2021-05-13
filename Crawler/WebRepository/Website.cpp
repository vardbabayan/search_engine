#include "Website.hpp"

Website::Website() 
    : id{id}, domain{domain}, homepage{homepage}, updated{updated}
{
}

Website::Website(const std::string& domain, const std::string& homePage, std::time_t time)
    : domain{domain}, homepage{homePage}, updated{time}
{
}


Website::Website(int id, const std::string& domain, const std::string& homePage, std::time_t time)
    : id{id}, domain{domain}, homepage{homePage}, updated{time}
{
}

int Website::getId() const
{
    return id;
}

std::string Website::getDomain() const
{
    return domain;
}

std::string Website::getHomePage() const
{
    return homepage;
}

std::time_t Website::getLastCrawleTime() const
{
    return updated;
}