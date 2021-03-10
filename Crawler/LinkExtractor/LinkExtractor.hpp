#include "HtmlDocument/HtmlDocument.hpp"

#include <vector>

class LinkExtractor
{
public:
    LinkExtractor();
    std::vector<std::string> extract(const HtmlDocument& doc);
};