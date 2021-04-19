#include "DocumentRepository.hpp"

std::vector<Document> DocumentRepository::getAll() const
{
    return docSource;
}

std::vector<Document> DocumentRepository::getByUrl(const std::string& url) const
{
    std::vector<Document> docRep;
    for(const auto& doc : docSource)
    {
        if(doc.getUrl() == url)
            docRep.push_back(doc);
    }

    return docRep;
}

 void DocumentRepository::save(const Document& doc)
 {
     for(int i = 0; i < docSource.size(); ++i)
     {
         if(docSource[i].getUrl() == doc.getUrl())
         {
            docSource[i] = doc;
            return;
         }
     }

     docSource.push_back(doc);
 }