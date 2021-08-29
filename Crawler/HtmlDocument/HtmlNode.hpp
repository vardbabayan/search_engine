#ifndef HTML_NODE
#define HTML_NODE

#include <gumbo.h>

class HtmlNode
{
protected:
    /**
     * node is representing part of HTML Tree
     */
    GumboNode* node;
public:
    explicit HtmlNode(GumboNode* node);

    /**
     * check is node Element in the HTML Tree or not
     */
    virtual bool isElement() const;
};

#endif
