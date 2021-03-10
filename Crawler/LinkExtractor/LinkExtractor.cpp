#include "LinkExtractor.hpp"

std::vector<std::string> LinkExtractor::extract(const HtmlDocument& doc)
{
    std::vector<std::string> links;
    doc.visitElements([&links](HtmlElement elem){ 
        if(!elem.isTagA())
        {
            return;
        }

        auto href = elem.getAttribute("href");
        /* if(href) //check size of href
        */

       links.push_back(href);
    });
}