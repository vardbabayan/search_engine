#include "LinkRepository.hpp"

// Push to vector and return all Links 
std::vector<LinkEntry> LinkRepository::getAll()
{
    std::vector<LinkEntry> links;
    for(const auto& tempLink : source)
        links.push_back(tempLink.second);

    return links;
}

// return Link id if it exist in source
LinkEntry LinkRepository::getById(int id)
{
    auto link = source.find(id);
    if(link != source.end())
    {
        return link->second;
    }

    return LinkEntry();
}

// to save here Link or Update if Link isCrawled
void LinkRepository::save(LinkEntry entry)
{
    if(entry.isCrawle)
    {
        source[entry.id] = entry;        
    }
    else
    {
        source.insert(std::make_pair(entry.id, entry));
    }
}