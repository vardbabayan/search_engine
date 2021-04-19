#include "PageLoader/PageLoader.hpp"
#include "HtmlDocument/HtmlDocument.hpp"

#include "DocumentExtractor/DocumentExtractor.hpp"
#include "DocumentRepository/DocumentRepository.hpp"

#include "LinkExtractor/LinkExtractor.hpp"
#include "LinkRepository/LinkRepository.hpp"
#include "LinkRepository/LinkStatus.hpp"

#include "WebRepository/WebRepository.hpp"

int main()
{
    std::time_t currentTime{};
    
    WebRepository webrep;
    webrep.save(WebSite("rau.am", "https://rau.am/", time(&currentTime)));

    LinkRepository linkrep;
    DocumentRepository docrep;
    PageLoader pageLoader;
    LinkExtractor linkExtractor;
    DocumentExtractor docExtractor;

    for(auto& website : webrep.getAll())
    {
        linkrep.save(LinkEntry(website.getHomePage(), website.getDomain(), LinkStatus::WAITING, time(&currentTime)));

        while(true)
        {
            auto links = linkrep.getBy(website.getDomain(), LinkStatus::WAITING, 10);

            if(links.empty()) 
            {
                break;
            }

            for(int i = 0; i < links.size(); ++i)
                std::cout << "Domain: " << links[i].getDomain() << " Url: " << links[i].getUrl() << "\n";

            for(auto& link : links)
            {
                auto loadResult = pageLoader.loadURL(link.getUrl());
                
                if(loadResult.getStatus() < 200 || loadResult.getStatus() >= 300)
                {
                    linkrep.save(LinkEntry(link.getUrl(), link.getDomain(), LinkStatus::ERROR, time(&currentTime)));
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

                    linkrep.save(LinkEntry(newLink, website.getDomain(), LinkStatus::WAITING, time(&currentTime)));
                }

                auto docInfo = docExtractor.extractInfo(doc);
                docrep.save(Document(link.getUrl(), docInfo.getTitle(), docInfo.getText(), docInfo.getDescription(), time(&currentTime)));

                std::cout << "Title: " << docInfo.getTitle() << "\n Description: " << docInfo.getDescription() << "\n" 
                          << "Text: " << docInfo.getText() << "\n";

                linkrep.save(LinkEntry(link.getUrl(), link.getDomain(), LinkStatus::SUCCESS, time(&currentTime)));
            }
            std::cout << "links: " << linkrep.getCounter() << " " << "\n";
            
        }

        webrep.save(WebSite(website.getDomain(), website.getHomePage(), time(&currentTime)));
    }

    std::cout << "\nSuccessfully finished all \n";
}