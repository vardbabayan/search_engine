#ifndef Link_Extractor
#define Link_Extractor

#include "HtmlDocument/HtmlDocument.hpp"

#include <vector>

class LinkExtractor
{
public:
    LinkExtractor();
    std::vector<std::string> extract(HtmlDocument& doc);
};

#endif