#ifndef Html_Node
#define Html_Node

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