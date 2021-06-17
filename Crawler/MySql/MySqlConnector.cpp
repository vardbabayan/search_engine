#include "MySqlConnector.hpp"

MySqlConnector::MySqlConnector()
{
}
    
MySqlConnector::MySqlConnector(const std::string& host, unsigned int port, const std::string& username, 
                                                 const std::string& passwd, const std::string& dbname)
    : host{host}, port{port}, name{username}, passwd{passwd}, dbname{dbname}
{
}
    
MySqlConnector::~MySqlConnector()
{
}

std::string MySqlConnector::getHost() const
{
    return this->host;
}

std::string MySqlConnector::getName() const
{
    return this->name;
}

std::string MySqlConnector::getPassword() const
{
    return this->passwd;
}

std::string MySqlConnector::getDbName() const
{
    return this->dbname;
}

unsigned int MySqlConnector::getPort() const
{
    return this->port;
}