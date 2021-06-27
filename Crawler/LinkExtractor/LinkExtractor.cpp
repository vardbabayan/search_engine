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

std::string LinkExtractor::trim(const std::string& str)
{
    size_t start = str.find_first_not_of(" \n\r\t");
    size_t until = str.find_last_not_of(" \n\r\t");
    std::string::const_iterator i = start == std::string::npos ? str.begin() : str.begin() + start;
    std::string::const_iterator x = until == std::string::npos ? str.end()   : str.begin() + until+1;
    
    return std::string(i,x);
}
 
std::pair<std::string, std::string> LinkExtractor::check_url(const std::string& url) 
{
    std::string path, domain, x, protocol, port, query;
    int offset = 0;
    size_t pos1,pos2,pos3,pos4;

    x = trim(url);

    offset = offset==0 && x.compare(0, 8, "https://")==0 ? 8 : offset;
    offset = offset==0 && x.compare(0, 7, "http://" )==0 ? 7 : offset;

    pos1 = x.find_first_of('/', offset+1 );
    
    path = pos1==std::string::npos ? "" : x.substr(pos1);
    
    domain = std::string( x.begin()+offset, pos1 != std::string::npos ? x.begin()+pos1 : x.end() );
    
    path = (pos2 = path.find("#")) != std::string::npos ? path.substr(0,pos2) : path;
    
    port = (pos3 = domain.find(":")) != std::string::npos ? domain.substr(pos3+1) : "";
    
    domain = domain.substr(0, pos3 != std::string::npos ? pos3 : domain.length());
    
    protocol = offset > 0 ? x.substr(0,offset-3) : "";
    
    query = (pos4 = path.find("?")) !=std::string::npos ? path.substr(pos4+1) : "";
    
    path = pos4 != std::string::npos ? path.substr(0,pos4) : path;

    return std::make_pair(protocol, domain);
}

std::vector<std::pair<std::string, std::string> > LinkExtractor::parse_url(std::vector<std::string>& links, const std::string& currentDomain)
{
    std::vector<std::pair<std::string, std::string> > result;
    
    for(auto& link : links) 
    {
        if(link[0] == '/' || link.size() < 4)
            continue;

        auto res = check_url(link);
        if(res.first == "https" || res.first == "http") 
        {
            if(res.second != currentDomain) 
            {   
                result.push_back(std::make_pair(res.second, link));
                std::remove(links.begin(), links.end(), link);
            }
        }
    }
    
    return result;
}