#ifndef Html_Node
#define Html_Node

#include <gumbo.h>

class HtmlNode
{
protected:
    GumboNode* node;
public:
    HtmlNode(GumboNode* node);
    virtual bool isElement();
};

#endif