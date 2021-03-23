#ifndef Html_Document
#define Html_Document


#include "HtmlElement.hpp"
#include <functional>
#include "gumbo.h"

class HtmlDocument 
{
private:
    GumboOutput* output;
    std::string url;

    void visitElement(GumboNode* node, std::function<void(HtmlElement)> visitor);
public:
    HtmlDocument(const std::string& url);
    bool parse();

    // call it to visit all vertexes
    void visitElements(std::function<void(HtmlElement)> visitor);
};

#endif