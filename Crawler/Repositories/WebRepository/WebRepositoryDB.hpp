#ifndef WEB_REPOSITORY_DB
#define WEB_REPOSITORY_DB

#include "../MySqlConnector/MySqlConnector.hpp"
#include "Website.hpp"
#include <iostream>
#include <vector>

class WebRepositoryDB
{
private:
    MySqlConnector connector;
    std::vector<Website> source;

public:
    WebRepositoryDB(const MySqlConnector& obj);
    std::vector<Website> getAll();

    void save(const Website& website);
};

#endif
