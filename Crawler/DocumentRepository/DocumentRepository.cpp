#include "DocumentRepository.hpp"

DocumentRepository::DocumentRepository(MysqlConnector* obj)
{
    this->connector = obj;
}

std::vector<Document> DocumentRepository::getAll() const
{
    auto all = connector->connect<std::vector<Document> >( [](MYSQL* mysql) 
    {
        MYSQL_RES* res;
        MYSQL_ROW row;
        std::vector<Document>  result;

        std::string query = "SELECT * FROM Documents";
        mysql_query(mysql, query.c_str());

        res = mysql_store_result(mysql);
        if(!res)
        {
            std::cout << "result error \n";
            return std::make_optional<std::vector<Document> >();
        }
        
        while(row = mysql_fetch_row(res))
        {
            size_t id = std::stoi(row[0]);
            std::string url = row[1];
            std::string title = row[2];
            std::string description = row[3];
            std::string text = row[4];
            
            result.push_back(Document(id, url, title, description, text));
        }

        mysql_free_result(res);
        return std::make_optional(result);
    });

    if(all.has_value())
    {
        std::vector<Document> res = all.value();
        for(int i = 0; i < res.size(); ++i)
        {
            std::cout << "DOC FROM: " << res[i].getUrl() << "\n";
        }
        return all.value();
    }

    return {};
}

std::optional<Document> DocumentRepository::getByUrl(const std::string& url) const
{
    auto doc = connector->connect<Document>([url](MYSQL* mysql)
    {
        MYSQL_RES* res;
        MYSQL_ROW row;
        std::vector<Document> doc;

        std::string query = "SELECT * FROM Documents WHERE url='" + url + "'";
        mysql_query(mysql, query.c_str());

        res = mysql_store_result(mysql);
        if(!res)
        {
            std::cout << "result error \n";
            return std::make_optional(Document());
        }
        
        while(row = mysql_fetch_row(res))
        {
            if(row[1] == url)
            {
                size_t id = std::stoi(row[0]);
                std::string url = row[1];
                std::string title = row[2];
                std::string description = row[3];
                std::string text = row[4];

                return std::make_optional(Document(id, url, title, description, text));
            }
        }

        mysql_free_result(res);
        std::cout << "DOCREP in getAll with query: " << query << "\n";
        return std::make_optional(Document());
    });

    if(doc.has_value())
        return doc;

    return {};
}

 void DocumentRepository::save(const Document& doc)
 {
     connector->connect<void*>([&doc](MYSQL* mysql)
     {
        MYSQL_RES* res;
        MYSQL_ROW row;
        
        std::string query = "SELECT * FROM Documents";
        mysql_query(mysql, query.c_str());
        
        res = mysql_store_result(mysql);
        if(!res)
        {
            std::cout << "result error \n";
            return nullptr;
        }
        
        bool find = false;
        while(row = mysql_fetch_row(res))
        {
            size_t id = std::stoi(row[0]);
            std::string url = row[1];
    
            if(url == doc.getUrl())
            {
                find = true;
                std::cout << "found link in db with id: " << id << " " << url << "\n";
                break;
            }
        }

        std::string tmpquery;
        if(find)
        {
            tmpquery = "UPDATE Documents SET `description`='" + doc.getDescription() + "', title='" 
                        + doc.getTitle()+ "', `text`='" + doc.getText() + "'" + " WHERE url='" + doc.getUrl() + "'";
        }
        else
        {
            tmpquery = "INSERT INTO Documents(url, `description`, title, `text`) VALUES ( '" + doc.getUrl() +"'"
                        + ", '" + doc.getDescription() + "', '" + doc.getTitle() + "', '" + doc.getText() + "' )";
        }

        mysql_query(mysql, tmpquery.c_str());

        std::string err = mysql_error(mysql);
        if(err.size() > 0)
        {
            std::cout  << "In DOCREP ERROR: " << err << "\n";
            //std::cout << "WITH QUERY: " << tmpquery << "\n";
        }

        mysql_free_result(res);
        return nullptr;
     });
 }