#include "LinkRepository.hpp"

LinkRepository::LinkRepository(MysqlConnector* obj)
{
    this->connector = obj;
}

std::vector<LinkEntry> LinkRepository::getAll() const
{
    auto all = connector->connect<std::vector<LinkEntry> >( [](MYSQL* mysql) 
    {
        MYSQL_RES* res;
        MYSQL_ROW row;
        std::vector<LinkEntry>  result;

        std::string query = "select * from Links";
        mysql_query(mysql, query.c_str());

        res = mysql_store_result(mysql);
        if(!res)
        {
            return std::make_optional<std::vector<LinkEntry> >(NULL);
        }

        unsigned int size =  mysql_field_count(mysql);
        
        while(row = mysql_fetch_row(res))
        {
            unsigned int id = int(*row[0] - '0');
            std::string url = row[1];
            unsigned int websiteid = int(*row[2] - '0');
            int status = int(*row[3] - '0');
            std::time_t time = std::time_t(row[4]);
            
            result.push_back(LinkEntry(id, url, websiteid, status, time));
        }

        mysql_free_result(res);

        return std::make_optional(result);
    });

    if(all.has_value())
    {
        return all.value();
    }

    return std::vector<LinkEntry>();
}

std::vector<LinkEntry> LinkRepository::getBy(int websiteId, int status, int count) const
{
    auto allBy = connector->connect<std::vector<LinkEntry> >([&websiteId](MYSQL* mysql)
    {
        MYSQL_RES* res;
        MYSQL_ROW row;
        std::vector<LinkEntry> links;

        std::string query = "select * from Links where websiteid=" + std::to_string(websiteId);
        mysql_query(mysql, query.c_str());

        res = mysql_store_result(mysql);
        if(!res)
        {
            return std::make_optional<std::vector<LinkEntry> >(NULL);
        }
        
        while(row = mysql_fetch_row(res))
        {
            unsigned int id = int(*row[0] - '0');
            std::string url = row[1];
            unsigned int websiteid = int(*row[2] - '0');
            int status = int(*row[3] - '0');
            std::time_t time = std::time_t(row[4]);
            
            links.push_back(LinkEntry(id, url, websiteid, status, time));
        }

        mysql_free_result(res);

        return std::make_optional(links);
    });

    if(allBy.has_value())
    {
        return allBy.value();
    }

    return std::vector<LinkEntry>();

    // std::vector<LinkEntry> domainSrc;
    // int counter = 0;
    // for(const auto& link : source)
    // {
    //     if(counter == count)
    //         break;

    //     if(link.websiteId == websiteId && link.status == status)
    //     {
    //         domainSrc.push_back(link);
    //         ++counter;
    //     }
    // }

    // return domainSrc;
}

std::optional<LinkEntry> LinkRepository::getByUrl(const std::string& url) const
{
    auto link = connector->connect<LinkEntry>([url](MYSQL* mysql)
    {
        MYSQL_RES* res;
        MYSQL_ROW row;

        std::string query = "select * from Links where url=" + url;
        mysql_query(mysql, query.c_str());

        res = mysql_store_result(mysql);
        if(!res)
        {
            return std::make_optional(LinkEntry());
        }
        
        while(row = mysql_fetch_row(res))
        {
            if(row[1] == url)
            {
                unsigned int id = int(*row[0] - '0');
                std::string url = row[1];
                unsigned int websiteid = int(*row[2] - '0');
                int status = int(*row[3] - '0');
                std::time_t time = std::time_t(row[4]);

                return std::make_optional(LinkEntry(id, url, websiteid, status, time));
            }
        }

        mysql_free_result(res);
        return std::make_optional(LinkEntry());
    });

    return link;

    // for(const auto& link : source)
    // {
    //     if(link.url == url)
    //     {
    //         return std::make_optional(link);
    //     }
    // }

    // return {};
}

void LinkRepository::save(LinkEntry entry)
{
    connector->connect<void*>([&entry](MYSQL* mysql)
    {
        MYSQL_RES* res;
        MYSQL_ROW row;

        //std::string query = "UPDATE Links SET status=" + std::to_string(entry.getStatus()) + " where id=" + std::to_string(entry.getId()) + " AND url=" + entry.getUrl();
        
        std::string query = "SELECT * FROM Links";
        mysql_query(mysql, query.c_str());
        
        res = mysql_store_result(mysql);
        if(!res)
        {
            return nullptr;
        }
        
        bool find = false;
        while(row = mysql_fetch_row(res))
        {
            unsigned int id = int(*row[0] - '0');
            
            if(id == entry.getId())
            {
                find = true;
                break;
            }
        }

        std::string tmpquery;
        if(find)
        {
            tmpquery = "UPDATE Links SET status=" + std::to_string(entry.getStatus()) + " where id=" + std::to_string(entry.getId()) + " AND url=" + entry.getUrl();
        }
        else
        {
            tmpquery = "INSERT INTO Links(url, websiteid, `status`) values (" + entry.getUrl() + ", " + std::to_string(entry.getWebsiteId()) + ", " + std::to_string(entry.getStatus()) + ")";
        }

        mysql_query(mysql, tmpquery.c_str());

        mysql_free_result(res);

        return nullptr;
    });

    // for(int i = 0; i < source.size(); ++i)
    // {
    //     if(source[i].url == entry.url)
    //     {
    //         source[i] = entry;
    //         return;
    //     }
    // }

    // source.push_back(entry);
}