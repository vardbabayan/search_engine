#ifndef PAGE_LOADER_H
#define PAGE_LOADER_H

#include "LoadResult.h"

class PageLoader
{
public:
    LoadResult loadURL(const std::string url);
};

#endif