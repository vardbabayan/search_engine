#ifndef WEB_REPOSITORY
#define WEB_REPOSITORY

#include "WebSite.hpp"

#include <vector>

class WebRepository
{
private:
    std::vector<WebSite> source;

public:
    std::vector<WebSite> getAll() const;

    void save(const WebSite& website);
};

#endif
