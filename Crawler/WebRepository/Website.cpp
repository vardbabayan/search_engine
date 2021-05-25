#include "Website.hpp"

Website::Website() 
    : id{id}, domain{domain}, homepage{homepage}, updated{updated}
{
}

Website::Website(const std::string& domain, const std::string& homepage)
    : domain{domain}, homepage{homepage}
{
}

Website::Website(const std::string& domain, const std::string& homepage, std::time_t time)
    : domain{domain}, homepage{homepage}, updated{time}
{
}


Website::Website(int id, const std::string& domain, const std::string& homepage)
    : id{id}, domain{domain}, homepage{homepage}
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