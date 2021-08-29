#ifndef HTML_DOCUMENT
#define HTML_DOCUMENT

#include "HtmlElement.hpp"
#include <functional>
#include "gumbo.h"

class HtmlDocument 
{
private:
    /**
     * Stores output to traverse on Tree starting from root
     */
    GumboOutput* output;

    /**
     * Document for current url
     */  
    std::string html_code;

    /**
     * Visit all Nodes in Tree from root
     */
    void visitElement(GumboNode* node, std::function<void(HtmlElement)> visitor);

public:
    explicit HtmlDocument(const std::string& html);

    /**
     * parse HTML code to HTML Tree
     */
    bool parse();

    /**
     * visit all vertexes in the HTML Tree
     */
    void visitElements(std::function<void(HtmlElement)> visitor);

    /**
     * delete memory that allocated for GumboOutput* output
     */
    ~HtmlDocument();
};

#endif
