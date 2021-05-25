#ifndef LINK_EXTRACTOR
#define LINK_EXTRACTOR

#include "../HtmlDocument/HtmlDocument.hpp"
#include <iostream>
#include <vector>
#include <boost/regex.hpp>

class LinkExtractor
{
public:
    LinkExtractor() = default;

    // extract all links from current Document
    std::vector<std::string> extract(HtmlDocument& doc);

    void checkByDomain(std::vector<std::string>& links, const std::string& domain);
};

#endif