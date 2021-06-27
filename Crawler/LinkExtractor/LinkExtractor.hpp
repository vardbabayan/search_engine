#ifndef LINK_EXTRACTOR
#define LINK_EXTRACTOR

#include "../HtmlDocument/HtmlDocument.hpp"
#include <iostream>
#include <vector>
#include <boost/regex.hpp>

class LinkExtractor
{
private:
    std::string trim(const std::string& str);
    std::pair<std::string, std::string> check_url(const std::string& url);
public:
    LinkExtractor() = default;

    // extract all links from current Document
    std::vector<std::string> extract(HtmlDocument& doc);

    std::vector<std::pair<std::string, std::string> > parse_url(std::vector<std::string>& links, const std::string& currentDomain);
};

#endif