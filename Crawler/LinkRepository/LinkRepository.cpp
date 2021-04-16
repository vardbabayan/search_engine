#include "LinkRepository.hpp"


std::vector<LinkEntry> LinkRepository::getAll() const
{
    return source;
}

std::vector<LinkEntry> LinkRepository::getBy(const std::string& domain, LinkStatus status, int count) const
{
    std::vector<LinkEntry> domainSrc;
    int counter = 0;
    for(const auto& link : source)
    {
        if(counter == count)
            break;

        if(link.domain == domain && link.status == status)
        {
            domainSrc.push_back(link);
            ++counter;
        }
    }

    return domainSrc;
}

std::optional<LinkEntry> LinkRepository::getByUrl(const std::string& url) const
{
    for(const auto& link : source)
    {
        if(link.url == url)
        {
            return std::make_optional(link);
        }
    }

    return {};
}

void LinkRepository::save(LinkEntry entry)
{
    for(int i = 0; i < source.size(); ++i)
    {
        if(source[i].url == entry.url)
        {
            source[i] = entry;
            return;
        }
    }

    source.push_back(entry);
}