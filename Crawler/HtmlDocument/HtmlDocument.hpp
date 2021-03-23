#ifndef Html_Document
#define Html_Document


#include "HtmlElement.hpp"
#include <functional>
#include "gumbo.h"

class HtmlDocument 
{
private:
    /**
     * Stores output to traverse on tree from root
     */
    GumboOutput* output;

    /**
     * Document for current url
     */  
    std::string url;

    /**
     * Visit all Nodes in tree from root
     */
    void visitElement(GumboNode* node, std::function<void(HtmlElement)> visitor);

public:
    HtmlDocument(const std::string& url);

    // parse html to tree
    bool parse();

    // call it to visit all vertexes
    void visitElements(std::function<void(HtmlElement)> visitor);

    // free memory that allocated for GumboOutput* output
    ~HtmlDocument();
};

#endif