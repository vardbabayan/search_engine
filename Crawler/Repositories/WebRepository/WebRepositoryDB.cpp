#include "WebRepositoryDB.hpp"

WebRepositoryDB::WebRepositoryDB(const MySqlConnector& obj)
{
    this->connector = obj;
}

std::vector<Website> WebRepositoryDB::getAll()
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
        
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM Websites");
        
        while (res->next())  
        {
            int id = res->getInt(1);
            std::string domain = res->getString(2).asStdString();
            std::string homepage = res->getString(3).asStdString();
            
            this->source.push_back(Website(id, domain, homepage));
        }
        
        driver->threadEnd();
        con->close();

        delete con;
        delete stmt;
        delete res;

        return this->source;
    } 
    catch (sql::SQLException &e) 
    {
        std::cout << "# ERR: SQLException in " << __FILE__;

        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;

        return std::vector<Website>();
    }
}

void WebRepositoryDB::save(const Website& website)
{
    try 
    {
        sql::Driver* driver;
        sql::Connection* con;
        sql::PreparedStatement* pstmt;

        /* Create a connection */
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", connector.getName(), connector.getPassword());
        
        /* Connect to the MySQL dbname database */
        con->setSchema(connector.getDbName());

        pstmt = con->prepareStatement("INSERT INTO Websites(domain, homepage) VALUES(?, ?) ON DUPLICATE KEY UPDATE updated = CURRENT_TIMESTAMP()");        
        pstmt->setString(1, website.getDomain());
        pstmt->setString(2, website.getHomePage());
        pstmt->executeQuery();
        
        driver->threadEnd();
        con->close();

        delete pstmt;
        delete con;
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