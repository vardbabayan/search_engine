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
        
        std::vector<Website> result;
        
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM Websites");
        
        while (res->next()) 
        {
            int id = res->getInt(1); // getInt(1) returns the first column
            std::string domain = res->getString(2).asStdString();
            std::string homepage = res->getString(3).asStdString();
            
            result.push_back(Website(id, domain, homepage));
        }

        delete con;
        delete stmt;
        delete res;

        this->source = result;
        return result;
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
    std::cout << website.getDomain() << " " << website.getHomePage() << "\n";
    try 
    {
        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;          

        /* Create a connection */
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", connector.getName(), connector.getPassword());
        
        /* Connect to the MySQL dbname database */
        con->setSchema(connector.getDbName());

        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM Websites");
        
        bool find = false;
        int id;
        while (res->next()) 
        {
            id = res->getInt(1); // getInt(1) returns the first column
            std::string domain = res->getString(2).asStdString();
            std::string homepage = res->getString(3).asStdString();
            
            if(domain == website.getDomain())
            {
                std::cout << "found " << domain << " "  << website.getDomain() << "\n"; 
                find = true;
                break;
            }
        }


        if(find)
        {
            pstmt = con->prepareStatement("UPDATE Websites SET domain=(?) WHERE id=(?)");            
            pstmt->setString(1, website.getDomain());
            pstmt->setInt(2, id);

            pstmt->executeQuery();
        }
        else
        {
            pstmt = con->prepareStatement("INSERT INTO Websites(domain, homepage) VALUES (?, ?)");
            pstmt->setString(1, website.getDomain());
            pstmt->setString(2, website.getHomePage());
            
            pstmt->executeQuery();

            std::cout << "website saved\n";
            source.push_back(website);
        }

        delete stmt;
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