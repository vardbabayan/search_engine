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

        std::string query = "select * from Documents";
        mysql_query(mysql, query.c_str());

        res = mysql_store_result(mysql);
        if(!res)
        {
            return std::make_optional<std::vector<Document> >(NULL);
        }
        
        while(row = mysql_fetch_row(res))
        {
            unsigned int id = int(*row[0] - '0');
            std::string url = row[1];
            std::string title = row[2];
            std::string description = row[3];
            std::string text = row[4];
            std::time_t time = std::time_t(row[5]);
            
            result.push_back(Document(id, url, title, description, text, time));
        }

        mysql_free_result(res);

        return std::make_optional(result);
    });

    if(all.has_value())
    {
        return all.value();
    }

    return std::vector<Document>();

    // return docSource;
}

std::optional<Document> DocumentRepository::getByUrl(const std::string& url) const
{
    auto doc = connector->connect<Document>([url](MYSQL* mysql)
    {
        MYSQL_RES* res;
        MYSQL_ROW row;
        std::vector<Document> doc;

        std::string query = "select * from Documents where url=" + url;
        mysql_query(mysql, query.c_str());

        res = mysql_store_result(mysql);
        if(!res)
        {
            return std::make_optional(Document());
        }
        
        while(row = mysql_fetch_row(res))
        {
            if(row[1] == url)
            {
                unsigned int id = int(*row[0] - '0');
                std::string url = row[1];
                std::string title = row[2];
                std::string description = row[3];
                std::string text = row[4];
                std::time_t time = std::time_t(row[5]);

                return std::make_optional(Document(id, url, title, description, text, time));
            }
        }

        mysql_free_result(res);
        return std::make_optional(Document());
    });

    return doc;

    
    // std::vector<Document> docRep;
    // for(const auto& doc : docSource)
    // {
    //     if(doc.getUrl() == url)
    //         docRep.push_back(doc);
    // }

    // return docRep;
}

 void DocumentRepository::save(const Document& doc)
 {
     for(int i = 0; i < docSource.size(); ++i)
     {
         if(docSource[i].getUrl() == doc.getUrl())
         {
            docSource[i] = doc;
            return;
         }
     }

     docSource.push_back(doc);
 }