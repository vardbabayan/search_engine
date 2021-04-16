#ifndef LINK_EXTRACTOR
#define LINK_EXTRACTOR

#include "../HtmlDocument/HtmlDocument.hpp"
#include <vector>

class LinkExtractor
{
public:
    LinkExtractor() = default;

    // extract all links from current Document
    std::vector<std::string> extract(HtmlDocument& doc);
};

#endif