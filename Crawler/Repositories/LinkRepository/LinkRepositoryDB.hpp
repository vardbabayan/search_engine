#ifndef LINK_REPOSITORY_DB
#define LINK_REPOSITORY_DB

#include "../MySqlConnector/MySqlConnector.hpp"

#include "LinkEntry.hpp"
#include <vector>
#include <string>
#include <optional>

class LinkRepositoryDB
{
private:
    MySqlConnector connector;
    std::vector<LinkEntry> source;
    
public:
    LinkRepositoryDB(const MySqlConnector& obj);
    
    /**
    * Push to vector and return all Links 
    */
    std::vector<LinkEntry> getAll();
    
    /**
     * return Link by domain if it exists in source
     */
    std::vector<LinkEntry> getBy(size_t websiteId, size_t status, size_t count) const;
    
    /**
     * to save here Link or Update if Link isCrawled
     */
    std::optional<LinkEntry> getByUrl(const std::string& url) const;

    /**
     * save Link to the source
     */    
    void save(const LinkEntry& entry);

    int getSize();
};

#endif
