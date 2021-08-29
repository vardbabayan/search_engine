#ifndef DOCUMENT_EXTRACTOR
#define DOCUMENT_EXTRACTOR

#include "../HtmlDocument/HtmlDocument.hpp"
#include "DocumentInfo.hpp"

class DocumentExtractor
{
public:
    DocumentExtractor() = default;
    DocumentInfo extractInfo(HtmlDocument& doc);
};

#endif
