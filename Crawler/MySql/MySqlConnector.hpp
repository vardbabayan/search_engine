#ifndef MYSQL_CONNECTOR
#define MYSQL_CONNECTOR

//  #include "MySql.hpp"

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class MySqlConnector 
{
private:
    std::string host;
    std::string name;
    std::string passwd;
    std::string dbname;
    unsigned int port;

public:
    MySqlConnector();
    
    MySqlConnector(const std::string& host, unsigned int port, const std::string& username, 
                                     const std::string& passwd, const std::string& dbname);
    
    ~MySqlConnector();

    std::string getHost() const;
    std::string getName() const;
    std::string getPassword() const;
    std::string getDbName() const;
    unsigned int getPort() const;

    // template <typename T>
    // std::optional<T> connect(std::function<std::optional<T>(MySql)> function)
    // {
    //     MySql connector;

    //     sql::Driver *driver = connector.getDriver();
    //     sql::Connection *con = connector.getConnection();

    //     /* Create a connection */
    //     driver = get_driver_instance();
    //     con = driver->connect("tcp://127.0.0.1:3306", username, passwd);
        
    //     /* Connect to the MySQL dbname database */
    //     con->setSchema(dbname);

    //     std::optional<T> result = function(connector);

    //     connector.~MySql();
        
    //     return result;
    // }
};

#endif
