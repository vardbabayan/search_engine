#ifndef PAGE_LOADER_H
#define PAGE_LOADER_H

#include "LoadResult.hpp"

class PageLoader
{
private:
    /**
     * callback function to save html code
     */
    static size_t writeFunction(char *ptr, size_t size, size_t nmemb, void* data);
public:
    explicit PageLoader() = default;

    /**
     * loading html code from the page according to current url
     */
    LoadResult loadURL(const std::string& url);
};

#endif
