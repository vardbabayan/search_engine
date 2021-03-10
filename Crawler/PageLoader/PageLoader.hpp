#ifndef PAGE_LOADER_H
#define PAGE_LOADER_H

#include "LoadResult.hpp"

class PageLoader
{
private:
    static size_t writeFunction(char *ptr, size_t size, size_t nmemb, void* data);
public:
    PageLoader() = default;
    LoadResult loadURL(const std::string url);
};

#endif