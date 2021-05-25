#include "LinkRepository.hpp"

LinkRepository::LinkRepository(MysqlConnector* obj)
{
    this->connector = obj;
}

std::vector<LinkEntry> LinkRepository::getAll() const
{
    auto all = connector->connect<std::vector<LinkEntry> >([](MYSQL* mysql) 
    {
        MYSQL_RES* res;
        MYSQL_ROW row;
        std::vector<LinkEntry>  result;

        std::string query = "SELECT * FROM Links"; 
        mysql_query(mysql, query.c_str());

        if(!res)
        {
            std::cout << "result error \n";
            return std::make_optional<std::vector<LinkEntry> >();
        }

        unsigned int size =  mysql_field_count(mysql);
        
        while(row = mysql_fetch_row(res))
        {
            size_t id = std::stoi(row[0]);
            std::string url = row[1];
            size_t websiteid = std::stoi(row[2]);
            size_t status = std::stoi(row[3]);
            
            result.push_back(LinkEntry(url, websiteid, status));
        }

        mysql_free_result(res);
        return std::make_optional(result);
    });

    if(all.has_value())
    {
        std::vector<LinkEntry> res = all.value();
        for(int i = 0; i < res.size(); ++i)
        {
            std::cout << res[i].getUrl() << "\n";
        }
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

        std::string query = "SELECT * FROM Links WHERE websiteid=" + std::to_string(websiteId); 
        mysql_query(mysql, query.c_str());

        res = mysql_store_result(mysql);
        if(!res)
        {
            std::cout << "result error \n";
            return std::make_optional<std::vector<LinkEntry> >();
        }
        
        while(row = mysql_fetch_row(res))
        {
            size_t id = std::stoi(row[0]);
            std::string url = row[1];
            size_t websiteid = std::stoi(row[2]);
            size_t status = std::stoi(row[3]);
            
            links.push_back(LinkEntry(url, websiteid, status));
        }

        mysql_free_result(res);
        return std::make_optional(links);
    });

    if(allBy.has_value())
    {
        std::vector<LinkEntry> res = allBy.value();
        // for(int i = 0; i < res.size(); ++i)
        // {
        //     std::cout << res[i].getUrl() << "\n";
        // }
        return allBy.value();
    }

    return std::vector<LinkEntry>();
}

std::optional<LinkEntry> LinkRepository::getByUrl(const std::string& url) const
{
    auto link = connector->connect<LinkEntry>([url](MYSQL* mysql)
    {
        MYSQL_RES* res;
        MYSQL_ROW row;

        std::string query = "SELECT * FROM Links WHERE url='" + url + "'";
        mysql_query(mysql, query.c_str());

        res = mysql_store_result(mysql);
        if(!res)
        {
            std::cout << "result error\n";
            return std::make_optional(LinkEntry{});
        }
        
        while(row = mysql_fetch_row(res))
        {
            if(row[1] == url)
            {
                size_t id = std::stoi(row[0]);
                std::string url = row[1];
                size_t websiteid = std::stoi(row[2]);
                size_t status = std::stoi(row[3]);

                return std::make_optional(LinkEntry(url, websiteid, status));
            }
        }

        mysql_free_result(res);
        return std::make_optional(LinkEntry{});
    });

    return link;
}

void LinkRepository::save(LinkEntry entry)
{
    connector->connect<void*>([&entry](MYSQL* mysql)
    {
        MYSQL_RES* res;
        MYSQL_ROW row;

        std::string query = "SELECT * FROM Links";
        mysql_query(mysql, query.c_str());
        
        res = mysql_store_result(mysql);
        if(!res)
        {
            std::cout << "result error \n";
            return nullptr;
        }
        
        size_t id;
        bool find = false;
        while(row = mysql_fetch_row(res))
        {
            id = std::stoi(row[0]);
            std::string url = row[1];

            if(url == entry.getUrl())
            {
                find = true;
                break;
            }
        }

        std::string tmpquery;
        if(find)
        {
            tmpquery = "UPDATE Links SET `status`=" + std::to_string(entry.getStatus()) 
            + " WHERE url='" + entry.getUrl() + "'";
        }
        else
        {
            tmpquery = "INSERT INTO Links(url, websiteid, `status`) VALUES ( '" + entry.getUrl() + "'" 
            + ", " + std::to_string(entry.getWebsiteId()) + ", " + std::to_string(entry.getStatus()) + " )";
        }

        mysql_query(mysql, tmpquery.c_str());

        std::string err = mysql_error(mysql);
        if(err.size() > 0)
        {
            std::cout  << "In LINKREP ERROR: " << err << "\n";
        }

        //std::cout << "LINKREP IN save with query: " << query <<  "\n" << tmpquery << "\n";
        
        mysql_free_result(res);
        return nullptr;
    });
}

int LinkRepository::getSize()
{
    return source.size();
}