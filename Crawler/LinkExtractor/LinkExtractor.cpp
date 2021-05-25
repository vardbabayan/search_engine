#include "LinkExtractor.hpp"

// Extract all links from current URL and contain them in vector
std::vector<std::string> LinkExtractor::extract(HtmlDocument& doc)
{
    std::vector<std::string> links;
    doc.visitElements([&links](HtmlElement elem)
    { 
        if(!elem.isTagA())
        {
            return;
        }

        auto href = elem.getAttribute("href");
        if(href.size() > 0)
            links.push_back(href);
    });

    return links;
}

std::vector<std::pair<std::string, std::string> > LinkExtractor::checkByDomain(std::vector<std::string>& links, const std::string& domain)
{
    std::vector<std::pair<std::string, std::string> >  newDomains;
    for(auto& link : links)
    { 
        boost::regex ex("(http|https)://([^/ :]+):?([^/ ]*)(/?[^ #?]*)\\x3f?([^ #]*)#?([^ ]*)");
        boost::cmatch what;
        
        if(regex_match(link.c_str(), what, ex)) 
        {
            // std::string protocol = std::string(what[1].first, what[1].second);
            
            std::string currentDomain   = std::string(what[2].first, what[2].second);
            
            // std::string port     = std::string(what[3].first, what[3].second);
            // std::string path     = std::string(what[4].first, what[4].second);
            // std::string query    = std::string(what[5].first, what[5].second);

            if(currentDomain != domain)
            {                
                newDomains.push_back(std::make_pair(domain, link));
                std::cout << "[" << link << "]" << std::endl;
                std::cout << currentDomain << std::endl;
                std::remove(links.begin(), links.end(), link);
            }

            // std::cout << protocol << std::endl;
            // std::cout << port << std::endl;
            // std::cout << path << std::endl;
            // std::cout << query << std::endl;
        }
    }
    return newDomains;
}