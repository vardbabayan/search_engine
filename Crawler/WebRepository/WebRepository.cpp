#include "WebRepository.hpp"

WebRepository::WebRepository(MysqlConnector* obj)
{
    this->connector = obj;
}

std::vector<Website> WebRepository::getAll() const
{
    auto all = connector->connect<std::vector<Website> >([](MYSQL* mysql) 
    {
        MYSQL_RES* res;
        MYSQL_ROW row;
        std::vector<Website>  result;

        std::string query = "SELECT * FROM Websites";
        mysql_query(mysql, query.c_str());

        res = mysql_store_result(mysql);
        if(!res)
        {
            std::cout << "result error \n";
            return std::make_optional<std::vector<Website> >();
        }

        size_t size =  mysql_field_count(mysql);
        
        while(row = mysql_fetch_row(res))
        {
            size_t id = std::stoi(row[0]);
            std::string domain = row[1];
            std::string homepage = row[2];
            
            result.push_back(Website(id, domain, homepage));
        }

        mysql_free_result(res);
        //std::cout << "WEBREP in getAll with query: " << query << "\n";

        return std::make_optional(result);
    });

    if(all.has_value())
    {
        // std::cout << "HAS VALUE\n";
        //std::vector<Website> res = all.value();
        // for(int i = 0; i < res.size(); ++i)
        // {
        //     std::cout << res[i].getDomain() << " " << res[i].getId() << "\n";
        // }

        return all.value();
    }

    return std::vector<Website>();
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
            std::cout << "result error \n";
            return nullptr;
        }
        
        
        bool find = false;
        size_t id;
        while(row = mysql_fetch_row(res))
        {
            id = std::stoi(row[0]);

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
            tmpquery = "UPDATE Websites SET domain='" +  website.getDomain()
             + "'" + " WHERE id=" + std::to_string(id) + "";
        }
        else
        {
            tmpquery = "INSERT INTO Websites(domain, homepage) VALUES ( '" + website.getDomain() + "'"
             + " , '" + website.getHomePage() + "' )";
        }
        
        mysql_query(mysql, tmpquery.c_str());
        
        std::string str = mysql_error(mysql); 
        if(str.size() > 0)
        {
            std::cout << "ERROR IN WEBREP: " << str << "\n";
        }
        
       //std::cout << "SAVED INTO WEBREP USING THIS QUERY: " << tmpquery << "\n";
            
       mysql_free_result(res);
       return nullptr;
    });

}
// You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near '://rau.am/)' at 