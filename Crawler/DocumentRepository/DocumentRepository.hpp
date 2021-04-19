#ifndef Document_Repository
#define Document_Repository

#include "Document.hpp"

#include <vector>

class DocumentRepository
{
private:
    std::vector<Document> docSource;
public:
    std::vector<Document> getAll() const;

    std::vector<Document> getByUrl(const std::string& url) const;

    void save(const Document& doc);
};

#endif
