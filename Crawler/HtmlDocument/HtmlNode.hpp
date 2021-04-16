#ifndef HTML_NODE
#define HTML_NODE

#include <gumbo.h>

class HtmlNode
{
protected:
    /**
     * node to represent each node in htmlTree
     */
    GumboNode* node;
public:
    HtmlNode(GumboNode* node);

    // check is GumboNodeElement or not
    virtual bool isElement();
};

#endif
