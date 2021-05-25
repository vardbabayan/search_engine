#ifndef MYSQL_CONNECTOR
#define MYSQL_CONNECTOR

#include <mysql/mysql.h>
#include <iostream>
#include <functional>
#include <optional>

class MysqlConnector 
{
private:
    const char* host;
    const char* username;
    const char* passwd;
    const char* dbname;
    unsigned int port;

public:
    MysqlConnector();

    MysqlConnector(const char* host, unsigned int port, const char* username, const char* passwd, const char* dbname);

    MysqlConnector(const MysqlConnector& connector);

    template <typename T>
    std::optional<T> connect(std::function<std::optional<T>(MYSQL*)> function)
    {
        MYSQL* mysql = mysql_init(NULL);

        if(!mysql)
            return std::nullopt;

        if(!mysql_real_connect(mysql, this->host, this->username, this->passwd, this->dbname, this->port, NULL, 0))
        {
            return {};
        }

        std::optional<T> result = function(mysql);
        mysql_close(mysql);

        return result;
    }
};

#endif
