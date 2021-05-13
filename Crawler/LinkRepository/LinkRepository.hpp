#ifndef LINK_REPOSITORY
#define LINK_REPOSITORY

#include <mysql/mysql.h>
#include "../MysqlConnector/MysqlConnector.hpp"
#include "LinkEntry.hpp"
#include <vector>
#include <string>
#include <optional>

class LinkRepository
{
private:
    MysqlConnector* connector;
    std::vector<LinkEntry> source;
public:
    LinkRepository(MysqlConnector* obj);
    
    /**
    * Push to vector and return all Links 
    */
    std::vector<LinkEntry> getAll() const;
    
    /**
     * return Link by domain if it exists in source
     */
    std::vector<LinkEntry> getBy(int websiteId, int status, int count) const;
    
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
