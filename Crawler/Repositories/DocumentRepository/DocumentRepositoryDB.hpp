#ifndef DOCUMENT_REPOSITORY_DB
#define DOCUMENT_REPOSITORY_DB

#include "../MySqlConnector/MySqlConnector.hpp"
#include "Document.hpp"
#include <vector>

class DocumentRepositoryDB
{
private:
    MySqlConnector connector;
    std::vector<Document> docSource;
public:
    DocumentRepositoryDB(const MySqlConnector& obj);

    /**
     * return All Documents from source
     */
    std::vector<Document> getAll();

    /**
     * return Document definite by url
     */
    std::optional<Document> getByUrl(const std::string& url) const;


    /**
     * saving Document or updating info about it if already exists
     */
    void save(const Document& doc);
};

#endif
