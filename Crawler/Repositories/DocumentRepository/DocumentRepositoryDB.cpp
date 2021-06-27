#include "DocumentRepositoryDB.hpp"

DocumentRepositoryDB::DocumentRepositoryDB(const MySqlConnector& obj)
{
    this->connector = obj;
}

std::vector<Document> DocumentRepositoryDB::getAll()
{
    try 
    {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;

        /* Create a connection */
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", connector.getName(), connector.getPassword());
        
        /* Connect to the MySQL dbname database */
        con->setSchema(connector.getDbName());
        
        std::vector<Document> result;
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM Documents");
        
        while (res->next()) 
        {            
            std::string url = res->getString(2).asStdString();
            std::string title = res->getString(3).asStdString();
            std::string description = res->getString(4).asStdString();
            std::string text = res->getString(5).asStdString();

            result.push_back(Document(url, title, description, text));
        }

        delete con;
        delete stmt;
        delete res;

        this->docSource = result;
        return result;
    } 
    catch (sql::SQLException &e) 
    {
        std::cout << "# ERR: SQLException in " << __FILE__;

        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;

        return std::vector<Document>();
    }
}

std::optional<Document> DocumentRepositoryDB::getByUrl(const std::string& url) const
{
    Document doc;
    try 
    {
        sql::Driver *driver;
        sql::Connection *con;
        sql::PreparedStatement* pstmt;
        sql::ResultSet *res;

        /* Create a connection */
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", connector.getName(), connector.getPassword());
        
        /* Connect to the MySQL dbname database */
        con->setSchema(connector.getDbName());
        
        std::vector<Document> result;
        pstmt = con->prepareStatement("SELECT * FROM Documents WHERE url=(?)");
        pstmt->setString(1, url);
        res = pstmt->executeQuery();

        if(res->next()) 
        {            
            std::string findUrl = res->getString(2).asStdString();
            std::string title = res->getString(3).asStdString();
            std::string description = res->getString(4).asStdString();
            std::string text = res->getString(5).asStdString();

            doc = Document(url, title, description, text);
        }

        delete con;
        delete pstmt;
        delete res;
    } 
    catch (sql::SQLException &e) 
    {
        std::cout << "# ERR: SQLException in " << __FILE__;

        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }

    return doc;
}

 void DocumentRepositoryDB::save(const Document& doc)
 {
    try 
    {
        sql::Driver* driver;
        sql::Connection* con;
        sql::ResultSet* res;
        sql::PreparedStatement* pstmt;

        /* Create a connection */
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", connector.getName(), connector.getPassword());
        
        /* Connect to the MySQL dbname database */
        con->setSchema(connector.getDbName());
        
        pstmt = con->prepareStatement("REPLACE INTO Documents(url, title, `description`, `text`) VALUES(?, ?, ?, ?)"); 
        pstmt->setString(1, doc.getUrl());
        pstmt->setString(2, doc.getTitle());
        pstmt->setString(3, doc.getDescription());
        pstmt->setString(4, doc.getText());

        delete pstmt;
        delete con;
        delete res;
    }
    catch (sql::SQLException &e) 
    {
        std::cout << "# ERR: SQLException in " << __FILE__;

        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
 }