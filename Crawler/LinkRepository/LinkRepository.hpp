#ifndef LINK_REPOSITORY
#define LINK_REPOSITORY

#include "LinkEntry.hpp"
#include <vector>
#include <optional>

class LinkRepository
{
private:
    std::vector<LinkEntry> source;
public:

    /**
    * Push to vector and return all Links 
    */
    std::vector<LinkEntry> getAll() const;
    
    /**
     * return Link by domain if it exists in source
     */
    std::vector<LinkEntry> getBy(const std::string& domain, LinkStatus status, int count) const;
    
    /**
     * to save here Link or Update if Link isCrawled
     */
    std::optional<LinkEntry> getByUrl(const std::string& url) const;

    /**
     * save Link to the source
     */    
    void save(LinkEntry entry);

    int getCounter()
    {
        return source.size();
    }
};

#endif
