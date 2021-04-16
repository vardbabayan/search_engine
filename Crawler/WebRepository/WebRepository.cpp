#include "WebRepository.hpp"

std::vector<WebSite> WebRepository::getAll() const
{
    return source;
}

void WebRepository::save(const WebSite& website)
{
    source.push_back(website);
}