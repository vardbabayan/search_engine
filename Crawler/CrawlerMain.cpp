#include "PageLoader/PageLoader.hpp"
#include "HtmlDocument/HtmlDocument.hpp"
#include "DocumentExtractor/DocumentExtractor.hpp"
#include "DocumentRepository/DocumentRepository.hpp"
#include "LinkExtractor/LinkExtractor.hpp"
#include "LinkRepository/LinkRepository.hpp"
#include "LinkRepository/LinkStatus.hpp"
#include "WebRepository/WebRepository.hpp"
#include "MysqlConnector/MysqlConnector.hpp"

  
    
const char* host = "localhost";
const char* name = "user";
const char* passwd = "password";
const char* dbname = "db_crawler";
unsigned int port = 3306;

int main()
{
    std::time_t currentTime{};

    MysqlConnector* connector = new MysqlConnector(host, port, name, passwd, dbname);
    WebRepository webrep(connector);
    
    //webrep.save(Website("globbing.com", "https://am.globbing.com/hy"));
    webrep.save(Website("rau.am", "https://rau.am/"));
    
    LinkRepository linkrep(connector);
    DocumentRepository docrep(connector);
    PageLoader pageLoader;
    LinkExtractor linkExtractor;
    DocumentExtractor docExtractor;

    for(auto& website : webrep.getAll())
    {
        linkrep.save(LinkEntry(website.getHomePage(), website.getId(), int(LinkStatus::WAITING)));

        while(true)
        {
            auto links = linkrep.getBy(website.getId(), int(LinkStatus::WAITING), 10);

            if(links.empty()) 
            {
                break;
            }

            // for(int i = 0; i < links.size(); ++i)
               //  std::cout << "Domain: " << links[i].getId() << " Url: " << links[i].getUrl() << "\n";

            for(auto& link : links)
            {
                auto loadResult = pageLoader.loadURL(link.getUrl());
                
                int status = loadResult.getStatus();
                if(status < 200 || status >= 300)
                {
                    std::cout << "wrong status \n";
                    linkrep.save(LinkEntry(link.getUrl(), link.getWebsiteId(), int(LinkStatus::ERROR)));
                    continue;
                }

                const std::string html = *loadResult.getBody().get();
                HtmlDocument doc(html);

                doc.parse();
                
                auto extractedLinks = linkExtractor.extract(doc);
                std::vector<std::pair<std::string, std::string> >  newDomains = linkExtractor.checkByDomain(extractedLinks, website.getDomain());
                
                // save new Domains
                for(auto& newDomain : newDomains)
                    webrep.save(Website(newDomain.first, newDomain.second));

                for(auto& newLink : extractedLinks)
                {
                    if(linkrep.getByUrl(newLink).value().getUrl() != "")
                    {
                        // std::cout << "already exists\n";
                        continue;
                    }
                    linkrep.save(LinkEntry(newLink, website.getId(), int(LinkStatus::WAITING)));
                }

                auto docInfo = docExtractor.extractInfo(doc);
                docrep.save(Document(link.getUrl(), docInfo.getTitle(), docInfo.getText(), docInfo.getDescription()));

                // std::cout << "Title: " << docInfo.getTitle() << "\n Description: " << docInfo.getDescription() << "\n" 
                //           << "Text: " << docInfo.getText() << "\n";

                std::cout << "successfully saved\n";
                linkrep.save(LinkEntry(link.getUrl(), link.getWebsiteId(), int(LinkStatus::SUCCESS)));
            }
            
            std::cout << "links: " << linkrep.getSize() << " " << "\n";
            return 0;
        }

        webrep.save(Website(website.getDomain(), website.getHomePage()));
    }

    std::cout << "\nSuccessfully finished all \n";
}