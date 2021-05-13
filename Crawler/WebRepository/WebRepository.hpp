#ifndef WEB_REPOSITORY
#define WEB_REPOSITORY

#include "../MysqlConnector/MysqlConnector.hpp"
#include "Website.hpp"

#include <vector>

class WebRepository
{
private:
    MysqlConnector* connector;
    std::vector<Website> source;

public:
    WebRepository(MysqlConnector* obj);
    std::vector<Website> getAll() const;

    void save(const Website& website);
};

#endif
