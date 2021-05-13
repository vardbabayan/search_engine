#include "PageLoader/PageLoader.hpp"
#include "HtmlDocument/HtmlDocument.hpp"
#include "DocumentExtractor/DocumentExtractor.hpp"
#include "DocumentRepository/DocumentRepository.hpp"
#include "LinkExtractor/LinkExtractor.hpp"
#include "LinkRepository/LinkRepository.hpp"
#include "LinkRepository/LinkStatus.hpp"
#include "WebRepository/WebRepository.hpp"
#include "MysqlConnector/MysqlConnector.hpp"

int main()
{
    std::time_t currentTime{};
    
    MysqlConnector* connector = new MysqlConnector();
    WebRepository webrep(connector);
    webrep.save(Website("rau.am", "https://rau.am/", time(&currentTime)));

    LinkRepository linkrep(connector);
    DocumentRepository docrep(connector);
    PageLoader pageLoader;
    LinkExtractor linkExtractor;
    DocumentExtractor docExtractor;

    for(auto& website : webrep.getAll())
    {
        linkrep.save(LinkEntry(website.getId(), website.getHomePage(), int(LinkStatus::WAITING), time(&currentTime)));

        while(true)
        {
            auto links = linkrep.getBy(website.getId(), int(LinkStatus::WAITING), 10);

            if(links.empty()) 
            {
                break;
            }

            for(int i = 0; i < links.size(); ++i)
                std::cout << "Domain: " << links[i].getId() << " Url: " << links[i].getUrl() << "\n";

            for(auto& link : links)
            {
                auto loadResult = pageLoader.loadURL(link.getUrl());
                
                int status = loadResult.getStatus();
                if(status < 200 || status >= 300)
                {
                    linkrep.save(LinkEntry(link.getId(), link.getUrl(), link.getWebsiteId(), int(LinkStatus::ERROR), time(&currentTime)));
                    continue;
                }

                const std::string html = *loadResult.getBody().get();

                HtmlDocument doc(html);

                doc.parse();
                
                auto extractedLinks = linkExtractor.extract(doc);
                for(auto& newLink : extractedLinks)
                {
                    if(linkrep.getByUrl(newLink).has_value())
                    {
                        continue;
                    }

                    linkrep.save(LinkEntry(newLink, int(LinkStatus::WAITING), time(&currentTime)));
                }

                auto docInfo = docExtractor.extractInfo(doc);
                docrep.save(Document(link.getUrl(), docInfo.getTitle(), docInfo.getText(), docInfo.getDescription(), time(&currentTime)));

                // std::cout << "Title: " << docInfo.getTitle() << "\n Description: " << docInfo.getDescription() << "\n" 
                //           << "Text: " << docInfo.getText() << "\n";

                linkrep.save(LinkEntry(link.getId(), link.getUrl(), link.getWebsiteId(), int(LinkStatus::SUCCESS), time(&currentTime)));
            }
            
            std::cout << "links: " << linkrep.getCounter() << " " << "\n";
            
        }

        webrep.save(Website(website.getDomain(), website.getHomePage(), time(&currentTime)));
    }

    std::cout << "\nSuccessfully finished all \n";
}