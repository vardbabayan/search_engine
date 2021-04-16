#ifndef HTML_DOCUMENT
#define HTML_DOCUMENT

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
    std::string html;

    /**
     * Visit all Nodes in tree from root
     */
    void visitElement(GumboNode* node, std::function<void(HtmlElement)> visitor);

public:
    HtmlDocument(const std::string& html);

    // parse html to tree
    bool parse();

    // call it to visit all vertexes
    void visitElements(std::function<void(HtmlElement)> visitor);

    // free memory that allocated for GumboOutput* output
    ~HtmlDocument();
};

#endif
