#include "WebRepository.hpp"

WebRepository::WebRepository(MysqlConnector* obj)
{
    this->connector = obj;
}

std::vector<Website> WebRepository::getAll() const
{
    auto all = connector->connect<std::vector<Website> >( [](MYSQL* mysql) 
    {
        MYSQL_RES* res;
        MYSQL_ROW row;
        std::vector<Website>  result;

        std::string query = "select * from Links";
        mysql_query(mysql, query.c_str());

        res = mysql_store_result(mysql);
        if(!res)
        {
            return std::make_optional<std::vector<Website> >(NULL);
        }

        unsigned int size =  mysql_field_count(mysql);
        
        while(row = mysql_fetch_row(res))
        {
            unsigned int id = int(*row[0] - '0');
            std::string domain = row[1];
            std::string homepage = row[2];
            std::time_t time = std::time_t(row[3]);
            
            result.push_back(Website(id, domain, homepage, time));
        }

        mysql_free_result(res);

        return std::make_optional(result);
    });

    if(all.has_value())
    {
        return all.value();
    }

    return std::vector<Website>();
    
    
    
    // return source;
}

void WebRepository::save(const Website& website)
{
    auto temp = connector->connect<void*>([&website](MYSQL* mysql)
    {
        MYSQL_RES* res;
        MYSQL_ROW row;

        std::string query = "SELECT * FROM Websites";
        mysql_query(mysql, query.c_str());
        
        res = mysql_store_result(mysql);
        if(!res)
        {
            return nullptr;
        }
        
        bool find = false;
        while(row = mysql_fetch_row(res))
        {
            std::string domain = row[1];
            
            if(domain == website.getDomain())
            {
                find = true;
                break;
            }
        }

        std::string tmpquery;
        if(find)
        {
            tmpquery = "UPDATE Websites SET updated=" + std::to_string(website.getLastCrawleTime()) + " where id=" + std::to_string(website.getId()) + " AND domain=" + website.getDomain();
        }
        else
        {
            tmpquery = "INSERT INTO Websites(domain, homepage) values (" + website.getDomain() + ", " + website.getHomePage() + ")";
        }

        mysql_query(mysql, tmpquery.c_str());

        mysql_free_result(res);

        return nullptr;
    });


    // for(int i = 0; i < source.size(); ++i)
    // {
    //     if(source[i].getDomain() == website.getDomain()) 
    //     {
    //         source[i] = website;
    //         return;
    //     }
    // }

    // source.push_back(website);
}