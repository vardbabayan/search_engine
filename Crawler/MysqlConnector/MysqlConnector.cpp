#include "MysqlConnector.hpp"

MysqlConnector::MysqlConnector()
    : host{}, port{}, username{}, passwd{}, dbname{}
{
}

MysqlConnector::MysqlConnector(const char* host, unsigned int port, const char* username, const char* passwd, const char* dbname)
    : host{host}, port{port}, username{username}, passwd{passwd}, dbname{dbname}
{
}

MysqlConnector::MysqlConnector(const MysqlConnector& connector)
    : host{connector.host}, port{connector.port}, username{connector.username}, passwd{connector.passwd}, dbname{connector.dbname}
{
}