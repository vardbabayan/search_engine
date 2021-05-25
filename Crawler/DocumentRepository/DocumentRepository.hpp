#ifndef Document_Repository
#define Document_Repository

#include "../MysqlConnector/MysqlConnector.hpp"
#include "Document.hpp"

#include <mysql/mysql.h>
#include <vector>

class DocumentRepository
{
private:
    MysqlConnector* connector;
    std::vector<Document> docSource;
public:
    DocumentRepository(MysqlConnector* obj);

    std::vector<Document> getAll() const;

    std::optional<Document> getByUrl(const std::string& url) const;

    void save(const Document& doc);
};

#endif
